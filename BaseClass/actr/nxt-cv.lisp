#+:packaged-actr (in-package :act-r)
#+(and :clean-actr (not :packaged-actr) :ALLEGRO-IDE) (in-package :cg-user)
#-(or (not :clean-actr) :packaged-actr :ALLEGRO-IDE) (in-package :cl-user)

(require-compiled "DMI" "ACT-R6:support;dmi")
(require-compiled "GENERAL-PM" "ACT-R6:support;general-pm")

;;;; ---------------------------------------------------------------------- ;;;;
;;;; module definition
;;;; ---------------------------------------------------------------------- ;;;;

(defstruct nxt-cv busy)

(defun nxt-cv-create (model-name)
 (declare (ignore model-name))
  
  ;;load libraries
	(ql:quickload "cffi")
	
	#+sbcl
	(progn
		(format t "sbcl")
		(sb-alien:load-shared-object "./libwrap.so")
	)
	
	#+clozure
	(progn
		(format t "clisp")
		(open-shared-library "./libwrap.so")
	)
	
	(load "./proxy.lisp")
	(load "./proxy-clos.lisp")
	
	(make-nxt-cv)
)

(defun nxt-cv-reset (nxt)
	(declare (ignore nxt))
	(chunk-type play-demo int)
	(define-chunks (demo isa play-demo))
)

(defun nxt-cv-delete (nxt)
 (declare (ignore nxt))
)

(defun nxt-cv-params (nxt param) ;getter and setter for the parameters
  	(if (consp param)
		(case (car param)
			(:busy
				(format t "~s ~s" nxt param)
				(setf (nxt-cv-busy nxt) (cdr param)))
			(t (print-warning "Wrong parameter")))
		(case param
			(:busy
				(nxt-cv-busy nxt))
			(t (print-warning "Wrong parameter")))
	)
)

(defun nxt-cv-requests (instance buffer-name chunk-spec)
(if (nxt-cv-busy instance)
	(model-warning "Request made to the ~S buffer while the nxt-cv module was busy. New request ignored." buffer-name)
	(let ()
		(setf (nxt-cv-busy instance) t)
		(case buffer-name
			(nxt-cv
				(case (chunk-spec-chunk-type chunk-spec)
					(play-demo 
						(setf num (nxt-play-demo))
						(EVAL (READ-FROM-STRING (format nil "(set-chunk-slot-value demo int ~D)" num)))
						(schedule-event-relative 0.1 'set-buffer-chunk ;scheduling the action to fill the buffer, so that it will be available for the next production
						:priority :min 
						:params '(nxt-cv demo :requested t) ;put into the $1 buffer the $2 chunk
						:output nil)
						(format t "finito")
						)
				);case
			);nxt-cv
		);case
		(setf (nxt-cv-busy instance) NIL)
	);let
);if
);defun

(defun nxt-cv-queries (nxt buffer query value) ;handles the queries to the buffers
  (declare (ignore buffer))
  (case query ;type of the query
    (state
     (case value
       (busy (nxt-cv-busy nxt))
       (free (not (nxt-cv-busy nxt)))
       (error nil)
       (t (print-warning "Bad state query to the ~s buffer" buffer))))
    (t (print-warning "Invalid query ~s to the ~s buffer" query buffer))
    ))

(defun nxt-play-demo ()
	(setf asd (make-instance 'proxy))
	
	#+sbcl
	(demo asd)
	
	#+clozure
	(test asd)
	;(CCL::CALL-IN-INITIAL-PROCESS (lambda () (demo asd)))
)

(define-module-fct 'nxt-cv ;name
                   '(nxt-cv) ;buffers
  (list
		(define-parameter :busy
			:documentation "state"
			:default-value nil
			:owner t)
		)

   :request 'nxt-cv-requests
   :query 'nxt-cv-queries

   :version "0.1"
   :documentation "Motor module for the lego nxt brick"
   :creation 'nxt-cv-create
   :reset 'nxt-cv-reset 
   :delete 'nxt-cv-delete
   :params 'nxt-cv-params
)