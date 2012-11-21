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

(setf asd (make-instance 'proxy))

#+sbcl
(demo asd)

#+clozure
(CCL::CALL-IN-INITIAL-PROCESS (lambda () (demo asd)))