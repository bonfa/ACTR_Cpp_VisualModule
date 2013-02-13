;#+clozure (defparameter ccl::fasl-version (ccl::target-fasl-version))
;#+clozure (load "/Users/stefano/ACT-R\ 6\ Standalone/quicklisp.lisp")
; (quicklisp-quickstart:install :path "/Users/stefano/ACT-R\ 6\ Standalone/quicklisp")
;#+clozure (load "/Users/stefano/ACT-R\ 6\ Standalone/quicklisp/setup.lisp")
;#+clozure (load "/Users/stefano/ACT-R\ 6\ Standalone/telepathy.lisp")

(clear-all)
(define-model test-nxt-motor
    
(chunk-type goal state)
(chunk-type receive command)
(chunk-type bbox x1 y1 x2 y2)
(chunk-type vertices1p x1 y1 rad)
(chunk-type vertices3p x1 y1 x2 y2 x3 y3)
(chunk-type vertices4p x1 y1 x2 y2 x3 y3 x4 y4)
(chunk-type object type bbox color vertices)
(chunk-type qrcode type content)
(chunk-type marker type id attitude_angle quadrilateral qrstatus qrcode)

(add-dm (goal ISA goal))

(p start
	=goal>
   		ISA goal
   		state nil
   	==>
   	=goal>
   		state start-reading
;   	+comm>
;		isa		listener
;		turn	on
)

(p start-reading
	=goal>
		isa 	goal
		state 	start-reading
	==>
	=goal>
		state 	receive-chunk
	+comm>
		isa receive
		command "getFeature"
)

(p nothing-to-read
	=goal>
		isa 	goal
		state 	receive-chunk
	?comm>
		buffer	empty
	==>
	=goal>
		state 	start-reading
)
; (spp nothing-to-read :u -10) ;grants the production "receive-chunk" to be run all the time it's needed

(p receive-object
	=goal>
		isa 	goal
		state 	receive-chunk
	=comm>
		isa		object
	==>
	+visual-location>
		ISA       		visual-location
		kind			oval
		color			red
	=goal>
		state 	read-visloc
	-comm> ;store in dm
)

(p read-visloc
	=goal>
		isa 	goal
		state 	read-visloc
	?visual-location>
		state	free
	=visual-location>
		isa		visual-location
	==>
	!eval! (buffer-chunk 'visual-location)
	=goal>
		state 	fine
	-comm> ;store in dm
)

(p no-visloc
	=goal>
		isa 	goal
		state 	read-visloc
	?visual-location>
		state	free
	?visual-location>
		buffer	empty
	==>
	=goal>
		state 	fine
	-comm> ;store in dm
)

(p receive-qr
	=goal>
		isa 	goal
		state 	receive-chunk
	=comm>
		isa		qrcode
	==>
	=goal>
		state 	fine
	-comm> ;store in dm
)

(p receive-marker-with-qr
	=goal>
		isa 	goal
		state 	receive-chunk
	=comm>
		isa		marker
		qrstatus	t
		qrcode		=qr
	==>
	!eval! (format t "qr!")
	=goal>
		state 	read-qr
	+retrieval> =qr
)

(p read-qr
	=goal>
		isa 	goal
		state 	read-qr
	=retrieval>
		isa		qrcode
		content	=s
	==>
	!eval! (format t "qr says: ~S" =s)
	=goal>
		state 	end
)

(p receive-marker-without-qr
	=goal>
		isa 	goal
		state 	receive-chunk
	=comm>
		isa		marker
		quadrilateral =q
		qrstatus	nil
	==>
	!eval! (format t "NO qr!")
	=goal>
		state 	read-quad
	+retrieval> =q
)

(p read-quad
	=goal>
		isa 	goal
		state 	read-quad
	=retrieval>
		isa		object
		type	"Quadrilateral"
		bbox	=bb
	==>
	=goal>
		state 	read-bbox
	+retrieval> =bb
)

(p no-quad
	=goal>
		isa 	goal
		state 	read-quad
	?retrieval>
		buffer	empty
		state	free
	==>
	=goal>
		state 	stop
)

(p turn-right
	=goal>
		isa 	goal
		state 	read-bbox
	=retrieval>
		isa		bbox
	>=	x1		100
		x1		=x1
	>	x2		100
		x2		=x2
	==>
	!eval! (format t "right! ~S ~S moving of ~S" =x1 =x2)
	=goal>
		state 	start-reading
)

(p turn-left
	=goal>
		isa 	goal
		state 	read-bbox
	=retrieval>
		isa		bbox
	<	x1		100
		x1		=x1
	<=	x2		100
		x2		=x2
	==>
	!eval! (format t "left! ~S ~S moving of ~S" =x1 =x2)
	=goal>
		state 	start-reading
)

(p go-straight
	=goal>
		isa 	goal
		state 	read-bbox
	=retrieval>
		isa		bbox
	<=	x1		100
		x1		=x1
	>=	x2		100
		x2		=x2
	==>
	!eval! (format t "straight! ~S ~S" =x1 =x2)
	=goal>
		state 	start-reading
)

(p no-bbox
	=goal>
		isa 	goal
		state 	read-bbox
	?retrieval>
		buffer	empty
		state	free
	==>
	=goal>
		state 	stop
)

(goal-focus goal)
)