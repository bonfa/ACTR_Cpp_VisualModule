(require :sb-bsd-sockets)
(sb-alien:load-shared-object "libserver.so")

(defvar s ())
(defvar stack ()) ;a list of lists '(name (messages))
(defvar proc nil)


(defun server (port)
(sb-alien:load-shared-object "libserver.so")
 
;(cl:defpackage "TEST-C-CALL" (:use "CL" "SB-ALIEN" "SB-C-CALL"))
;(cl:in-package "TEST-C-CALL")
 
 ;;; Define the record C-STRUCT in Lisp.
 (define-alien-type nil
	 (struct c-struct
			 (x int)
			 (s c-string)))
 
 ;;; Define the Lisp function interface to the C routine.  It returns a
 ;;; pointer to a record of type C-STRUCT.  It accepts four parameters:
 ;;; I, an int; S, a pointer to a string; R, a pointer to a C-STRUCT
 ;;; record; and A, a pointer to the array of 10 ints.
 ;;;
 ;;; The INLINE declaration eliminates some efficiency notes about heap
 ;;; allocation of alien values.
 (declaim (inline server))
 (define-alien-routine server
	 (* (struct c-struct))
   (i int))
 
 ;;; a function which sets up the parameters to the C function and
 ;;; actually calls it
 (defun call-cfun ()
 
	 (with-alien ((res (* (struct c-struct))
					   (server 5 )))
	   (format t "~&amp;back from C function~%") ; (slot res 'x))
 
		 ;; Deallocate result. (after we are done referring to it:
		 ;; "Pillage, *then* burn.")
		 (free-alien res)))
		 
(call-cfun)
)
       
(defun connect (server port &optional)
;"Returns a socket connected to SERVER:PORT.  If an error occurs, or the attempt times out after TIMOUT (default 5) secons, nil is returned."
   (when (and server port)
           (let ((socket (make-instance 'sb-bsd-sockets:inet-socket :type :stream :protocol :tcp)))
             (sb-bsd-sockets::socket-connect socket server port)
             socket)))

(defun send (client-name str &optional (host "127.0.0.1") (port 5556))
;"Print LINE to SOCKET.  CRLF is added.  Returns the number of bytes written."
	(let* ((addr (sb-bsd-sockets:make-inet-address host)) (socket (connect addr port)) (result nil))
   	(when (and socket str)
     	(sb-bsd-sockets::socket-send socket str nil)) ;(concatenate 'string str (list #\return #\newline)) nil))
    (setq result (sb-bsd-sockets::socket-receive socket nil 1048576))
    (format t "received ~s" result)))

(defun receive (client-name &optional (host "127.0.0.1") (port 5556) (maxsize 65536))
;"Reads one line from SOCKET, removes CRLF, and returns it.  The buffer size is 65536 bytes, unless MAXSIZE is specified.  If no result is received within TIMEOUT seconds (defaults to 5), nil is returned."
   (let* ((addr (sb-bsd-sockets:make-inet-address host)) (socket (connect addr port)))
   (when socket
       (values (sb-bsd-sockets::socket-receive socket nil maxsize)))))

(defun tcp-print (client-name object &optional (host "localhost") (port 5556))
;"Writes OBJECT to SOCKET so that it can be received using tcp-read."
     (send client-name
                    (let ((ostream (make-string-output-stream)))
                      (print object ostream)
                      (get-output-stream-string ostream)) host port))

(defun tcp-read (client-name &optional (host "localhost") (port 5556) (maxsize 1048576))
;"Reads and returns a lisp object from the connection SOCKET."
     (let ((s (receive client-name host port maxsize)))
       (when s
         (with-input-from-string (istream s) (read istream nil nil)))))

(defstruct telepathy host port id)

(defun telepathy-create (model-name)
(declare (ignore model-name))
(make-telepathy))

(defun telepathy-reset (instance)
(declare (ignore instance))
(chunk-type listener turn)
(chunk-type receive)
)

(defun telepathy-delete (instance)
(declare (ignore instance))
)

(defun telepathy-requests (instance buffer-name chunk-spec)
	(case buffer-name
		(comm
			(case (chunk-spec-chunk-type chunk-spec)
				 (listener ;used to turn on and off the server
 					(case (third (car (chunk-spec-slot-spec chunk-spec 'turn)))
 						(on (setq proc (sb-thread:make-thread (lambda () (server (telepathy-port instance))))))
 						(off (sb-thread:terminate-thread proc))
 						;(on (setq server-event (schedule-event-relative 0 'server :maintenance t :time-in-ms t :params (list (telepathy-port instance)))))
 						;(off (delete-event server-event)) ;stop server
 						(t (print-warning "Wrong parameter for the \"listener\" request"))
 					);case
 				);listener
				;(receive ;creates a new chunk from a chunk-spec and stuffs the buffer with it
				;	(let ((str (cadr (receive (telepathy-id instance) (telepathy-host instance) (telepathy-port instance)))))
				;	(if (eql str nil) nil		
				;		(EVAL (READ-FROM-STRING (format nil "(schedule-set-buffer-chunk 'comm
				;			(car (define-chunks-fct (list (chunk-spec-to-chunk-def ~S)))) 0 :module 'comm)"
				;			(read-from-string str)))) ;the chunk-spec received from the server
				;	));if
				;);receive
				(t ;as default send the chunk to the server
					; (print " \\ ")(print chunk-spec)(print " //")
					(if (send (telepathy-id instance)
							(format nil "~s" chunk-spec) ;encapsulate the structure in a string
								; (EVAL (READ-FROM-STRING (format nil "(define-chunk-spec ~s)" (buffer-read 'retrieval)))))
							(telepathy-host instance)
							(telepathy-port instance)) ;read from the buffer and convert into a chunk-spec
						(print-warning "Communication failed: register the client and try again")
					);if
					
					; (schedule-set-buffer-chunk 'comm (car(define-chunks-fct (list (chunk-spec-to-chunk-def chunk-spec)))) 0.1 :module 'comm)
				);else
			);case
		);comm
		(t (print-warning "requested the wrong buffer ~s" buffer-name))
	);case
)

(defun telepathy-queries (instance buffer query value) ;handles the queries to the buffers
(declare (ignore buffer))
(case query ;type of the query
	(state
		(case value
			(busy nil)
			(free t)
			(error nil)
			(t (print-warning "Bad state query to the ~s buffer" buffer))
		);case
	);state
; 	(register
; 		(register (telepathy-id instance) (telepathy-host instance) (telepathy-port instance))
; 	);register
; 	(leave
; 		(leave (telepathy-id instance) (telepathy-host instance) (telepathy-port instance))
; 	);leave
	(t (print-warning "Invalid query ~s to the ~s buffer" query buffer))
))

(defun telepathy-params (instance param) ;getter and setter for the parameters
(if (consp param)
	(case (car param)
		(:server-port
			(setf (telepathy-port instance) (cdr param))
		);port
		(:server-host
			(setf (telepathy-host instance) (cdr param)))
		(:client-id
			(setf (telepathy-id instance) (cdr param)))
		(t (print-warning "Wrong parameter"))
	);case
	(case param
		(:server-port
			(telepathy-port instance))
		(:server-host
			(telepathy-host instance))
		(:client-id
			(telepathy-id instance))
		(t (print-warning "Wrong parameter"))
	);case
))

(define-module-fct	'telepathy ;name
					'((comm nil nil nil nil)) ;buffers (register leave)
(list 
	(define-parameter :server-port
		:documentation "port to which the server accepts connections"
		:default-value 5556
		:valid-test (lambda (x)
			(and (integerp x) (> x 1024) (< x 65535)))
		:warning "invalid port number"
		:owner t)
	(define-parameter :server-host
			:documentation "host where the server listens"
			:default-value "127.0.0.1"
			:owner t)
	(define-parameter :client-id
			:documentation "this client's unique ID"
			:default-value (random 100 (make-random-state t))
			:owner t)
)

   :request 'telepathy-requests
   :query 'telepathy-queries
   :creation 'telepathy-create
   :reset 'telepathy-reset
   :delete 'telepathy-delete
   :params 'telepathy-params
)