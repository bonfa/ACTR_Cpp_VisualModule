#+sbcl (require :sb-bsd-sockets)
(ql:quickload "cl-json")
;#+clozure (defparameter ccl::fasl-version (ccl::target-fasl-version))
;#+clozure (load "/Users/stefano/ACT-R\ 6\ Standalone/quicklisp.lisp")
;#+clozure (quicklisp-quickstart:install :path "/Users/stefano/ACT-R\ 6\ Standalone/quicklisp")
;#+clozure (load "/Users/stefano/ACT-R\ 6\ Standalone/telepathy.lisp")
;;;;;;;;#+clozure (load "/Users/stefano/ACT-R\ 6\ Standalone/quicklisp/setup.lisp")
#+sbcl (defun shell (x) (run-program "/bin/sh" (list "-c" x) :output t))
(setq def-host "127.0.0.1");"132.230.17.10");
(setq def-port 4114)
(setq def-comm "{\"cmd\":\"getFeature\"}")
(setq socket nil)
;screen resolution
(setf XSCREEN 1280.0)
(setf YSCREEN 720.0)
(setf XVIEWPORT 800)
(setf YVIEWPORT 800)
(setf buttons ())

;;;;;;;;;;;;;;;;;MODEL INIT
(setf *actr-enabled-p* t)
(setq *cellwidth* 100)
(setq *margin* 100)
(setq *offset* 0)
(setq *cellcount* 6)
(setq *boardsize* (* *cellcount* *cellwidth*))

(defun s ()
	(reset)
	(reload)
	(init-window)	; initializes the window
	(if *actr-enabled-p*
		(do-experiment-model)
		(do-experiment-person)
	)
)

(defun do-experiment-model ()
	(proc-display :clear t)
	(run 100 :real-time t)
 )

(defun do-experiment-person ()
	(proc-display :clear t)
	(sleep 1)
)

(defun init-window () 
	(setf *screen* 	
		#+sbcl 	(open-exp-window "RushHour"
				:visible nil
				:width XVIEWPORT
				:height YVIEWPORT)
		#+clozure 	(open-exp-window "RushHour"
				:visible t
				:width XVIEWPORT
				:height YVIEWPORT)
	)
	(install-device *screen*)
)

(defun normalize-coord (coord is_vertical)
	(if is_vertical
		(round (/ (* coord YVIEWPORT) 100))
		(round (/ (* coord XVIEWPORT) 100)))
		;(round (/ (* coord YVIEWPORT) YSCREEN))
		;(round (/ (* coord XVIEWPORT) XSCREEN)))
)

(defun draw-bbox (bbox color)
	(let* (	(x (normalize-coord (cdar (first bbox)) nil))
			(y (normalize-coord (cdadr (first bbox)) t))
			(width (- (normalize-coord (cdar (second bbox)) nil) x))
			(height (- (normalize-coord (cdadr (second bbox)) t) y)))
	(format t "bbox: x ~S y ~S w ~S h ~S~%" x y width height)
	(add-button-to-exp-window :x x :y y	:height height :width width	:text "" :color	(intern (string-upcase color)))
	);let
)
;;;;;;;;;;;;;;;;;END MODEL INIT

;;;;;;;;;;;;;;;;;;SOCKET
(defvar s ())
(defvar stack ()) ;a list of lists (name (messages))
;(defvar proc nil)
       
#+sbcl (defun connect (server port &optional)
;"Returns a socket connected to SERVER:PORT.  If an error occurs, or the attempt times out after TIMOUT (default 5) secons, nil is returned."
   (when (and server port)
        (let ((socket (make-instance 'sb-bsd-sockets:inet-socket :type :stream :protocol :tcp)))
           	(sb-bsd-sockets::socket-connect socket server port)
           	socket)
    )
)

(defun send (client-name str &optional (host def-host) (port def-port))
;"Print LINE to SOCKET.  CRLF is added.  Returns the number of bytes written."
	#+sbcl 	(let* ((addr (sb-bsd-sockets:make-inet-address host)) (socket (connect addr port)) (result nil))
   			(when (and socket str)
     		(sb-bsd-sockets::socket-send socket str nil)))
    #+clozure (ccl:with-open-socket (socket :address-family :internet :type :stream :connect :active :remote-host host :remote-port port)
      				(format socket str))
)

(defun receive (client-name &optional (command def-comm) (host def-host) (port def-port) (maxsize 65536))
;"Reads one line from SOCKET, removes CRLF, and returns it.  The buffer size is 65536 bytes, unless MAXSIZE is specified.  If no result is received within TIMEOUT seconds (defaults to 5), nil is returned."
   	#+sbcl (let* ((addr (sb-bsd-sockets:make-inet-address host)) (socket (connect addr port)))
   		(when socket
   			(progn (sb-bsd-sockets::socket-send socket command nil)
   			;(sleep 2)
       		(values (sb-bsd-sockets::socket-receive socket nil maxsize)))))
	#+clozure (ccl:with-open-socket (socket :address-family :internet :type :stream :connect :active :remote-host host :remote-port port :external-format '(:character-encoding :ascii :line-termination :crlf))
      				(format socket command)
      				(finish-output socket)
      				(read-line socket)
      			)
)

;(loop while (not (equal #\] (elt str (- (length str) 1)))) do
;	(setf str (concatenate 'string str (read-line socket)))
;)

;(defun tcp-print (client-name object &optional (host def-host) (port def-port))
;"Writes OBJECT to SOCKET so that it can be received using tcp-read."
;     (send client-name
;                   (let ((ostream (make-string-output-stream)))
;                      (print object ostream)
;                      (get-output-stream-string ostream)) host port))

;(defun tcp-read (client-name &optional (host def-host) (port def-port) (maxsize 1048576))
;"Reads and returns a lisp object from the connection SOCKET."
;     (let ((s (receive client-name host port maxsize)))
;       (when s
;         (with-input-from-string (istream s) (read istream nil nil)))))
;;;;;;;;;;;;;;;;;;END SOCKET

;;;;;;;;;;;;;;;;;;JSON decoding

(defun parse-bbox (bbox)
	(setf chunk nil)
	(setf chunk (EVAL (READ-FROM-STRING (format nil "(car (add-dm (isa bbox x1 ~S y1 ~S x2 ~S y2 ~S)))"
		(normalize-coord (cdar (first bbox)) nil)
		(normalize-coord (cdadr (first bbox)) t)
		(normalize-coord (cdar (second bbox)) nil)
		(normalize-coord (cdadr (second bbox)) t)))))
	chunk
)

(defun parse-vertices (vert type)
	(setf chunk nil)
	(cond
	((equal "Circle" type) (format t "Circle!~%")
		(setf chunk (EVAL (READ-FROM-STRING (format nil "(car (add-dm (isa vertices1p x1 ~S y1 ~S rad ~S)))"
				(normalize-coord (cdar (first vert)) nil)
				(normalize-coord (cdadr (first vert)) t)
				(cdar (second vert)))))))
	((equal "Triangle" type) (format t "Triangle!~%")
		(setf chunk (EVAL (READ-FROM-STRING (format nil "(car (add-dm (isa vertices3p x1 ~S y1 ~S x2 ~S y2 ~S x3 ~S y3 ~S)))"
				(normalize-coord (cdar (first vert)) nil)
				(normalize-coord (cdadr (first vert)) t)
				(normalize-coord (cdar (second vert)) nil)
				(normalize-coord (cdadr (second vert)) t)
				(normalize-coord (cdar (third vert)) nil)
				(normalize-coord (cdadr (third vert)) t))))))
	((equal "Quadrilateral" type) (format t "Quadrilateral!~%")
		(setf chunk (EVAL (READ-FROM-STRING (format nil "(car (add-dm (isa vertices4p x1 ~S y1 ~S x2 ~S y2 ~S x3 ~S y3 ~S x4 ~S y4 ~S)))"
				(normalize-coord (cdar (first vert)) nil)
				(normalize-coord (cdadr (first vert)) t)
				(normalize-coord (cdar (second vert)) nil)
				(normalize-coord (cdadr (second vert)) t)
				(normalize-coord (cdar (third vert)) nil)
				(normalize-coord (cdadr (third vert)) t)
				(normalize-coord (cdar (fourth vert)) nil)
				(normalize-coord (cdadr (fourth vert)) t))))))
	(t (format t "error while parsing json: chunk type ~s ~s not recognized~%" (type-of type) type)))
	;(format t "chunk: ~s~%" chunk)
	chunk
)

(defun parse-json (list)
;;;;json-bind needs to escape all the uppercase letters with * (Type => *type)
	(setf chunk nil)
	(setf type (cdr (assoc ':*type list)))
	;(format t "parsing json: ~S~%" list)
			(cond 
				((equal "Marker" type) (format t "Marker!~%")
					(setf chunk (EVAL (READ-FROM-STRING (format nil "(car (add-dm (isa marker type ~S id ~S attitude_angle ~S quadrilateral ~S qrstatus ~S qrcode ~S)))"
					 type
					 (cdr (assoc ':*id list))
					 (cdr (assoc ':*attitudeangle list))
					 (parse-json (cdr (assoc ':*quadrilateral list)))
					 (cdr (assoc ':*qrstatus list))
					 (if (cdr (assoc ':*qrstatus list)) ;if qrstatus is false, no qrcode is retrieved
					 	(parse-json (cdr (assoc ':*qrcode list)))
					 	nil)
					 ))))
				) ;Marker
				((equal "QRCode" type) (format t "QRCode!~%")
					(setf chunk (EVAL (READ-FROM-STRING (format nil "(car (add-dm (isa qrcode type ~S content ~S)))"
					type
					(cdr (assoc ':*content list))))))
				) ;QRCode
				(t ;(format t "~S!~%" type)
					(setf chunk (EVAL (READ-FROM-STRING (format nil "(car (add-dm (isa object type ~S color ~S bbox ~S vertices ~S)))"
					 type
					 (cdr (assoc ':*color list))
					 (parse-bbox (cdr (assoc ':*bbox list)))
					 (parse-vertices (cdr (assoc ':*vertices list)) type)))))
					 ;draw the button on the visicon
					 (draw-bbox (cdr (assoc ':*bbox list)) (cdr (assoc ':*color list)))
				) ;t
			);cond
	;(format t "chunk: ~s~%" chunk)
	chunk
)

	;(setf list (json:decode-json-from-string string))
		;(EVAL (READ-FROM-STRING (format nil "(car (define-chunks-fct (list (chunk-spec-to-chunk-def 
			;(define-chunk-spec isa object type ~S color ~S bbox ~S vertices ~S)))))" type color bbox vertices)))

;;;;;;;;;;;;;;;;;;;;;END JSON

;;;;;;;;;;;;;;;;;;;MODULE DEFINITION

(defstruct telepathy host port id)

(defun telepathy-create (model-name)
	(declare (ignore model-name))
	(make-telepathy))

(defun telepathy-reset (instance)
	(declare (ignore instance))
	(chunk-type listener turn)
	(chunk-type bbox x1 y1 x2 y2)
	(chunk-type vertices1p x1 y1 rad)
	(chunk-type vertices3p x1 y1 x2 y2 x3 y3)
	(chunk-type vertices4p x1 y1 x2 y2 x3 y3 x4 y4)
	(chunk-type object type bbox color vertices)
	(chunk-type qrcode type content)
	(chunk-type marker type id attitude_angle quadrilateral qrstatus qrcode)
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
 						(on (shell "./test")) ;run the server
 						(off (shell "killall test"))
 						(t (print-warning "Wrong parameter for the \"listener\" request"))
 					);case
 				);listener
				(receive ;creates a new chunk from a chunk-spec and stuffs the buffer with it
					(setf command (third (car (chunk-spec-slot-spec chunk-spec 'command))))
					;(format t "command=~S~%" command)
					(cond 
						((equal command "getFeature")
							(let ((str (receive (telepathy-id instance) "{\"cmd\":\"getFeature\"}" (telepathy-host instance) (telepathy-port instance))))
							;(format t "~S" str)
							(if (eql str nil) nil
								(loop for elem in (with-input-from-string (s str) (json:decode-json s)) do ;(print str)
									(EVAL (READ-FROM-STRING (format nil "(schedule-set-buffer-chunk 'comm '~S 0 :module 'comm)"	(parse-json elem))))
								);loop
							));if
						)((equal command "getMarker")
							(let ((str (receive (telepathy-id instance) "{\"cmd\":\"getMarker\"}" (telepathy-host instance) (telepathy-port instance))))
							(if (eql str nil) nil	;TODO too many set-buffer-chunk!
								(loop for elem in (with-input-from-string (s str) (json:decode-json s)) do (print str)
									(EVAL (READ-FROM-STRING (format nil "(schedule-set-buffer-chunk 'comm '~S 0 :module 'comm)" (parse-json elem))))
								);loop
							));if
						)(t (format t "command not recognized~%") ;safe default
							(let ((str (receive (telepathy-id instance) def-comm (telepathy-host instance) (telepathy-port instance))))
							(if (eql str nil) nil	
								(loop for elem in (with-input-from-string (s str) (json:decode-json s)) do ;(print elem)
									(EVAL (READ-FROM-STRING (format nil "(schedule-set-buffer-chunk 'comm '~S 0 :module 'comm)" (parse-json elem))))
								);loop
							));if
						);t
					);case
					(proc-display :clear t)
				);receive
				(t ;as default send the chunk to the server
					; (print " \\ ")(print chunk-spec)(print " //")
					(if (send (telepathy-id instance)
							def-comm
							;(json:encode-json (EVAL (READ-FROM-STRING (format nil "(define-chunk-spec ~s)" (buffer-read 'retrieval)))))
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

;(schedule-set-buffer-chunk 'comm (car (define-chunks-fct (list (chunk-spec-to-chunk-def (json:decode-json str))))) 0 :module 'comm)
								
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
		:default-value def-port
		:valid-test (lambda (x)
			(and (integerp x) (> x 1024) (< x 65535)))
		:warning "invalid port number"
		:owner t)
	(define-parameter :server-host
			:documentation "host where the server listens"
			:default-value def-host
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
