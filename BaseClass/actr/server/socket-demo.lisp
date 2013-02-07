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

;(p wait
;	=goal>
;	isa goal
;	state back
;	?comm>
;		state	free
;	==>
;	+comm>
;		isa goal
;		state	nil
;	=goal>
;		state	fine)

(p start-reading
	=goal>
		isa 	goal
		state 	start-reading
	==>
	=goal>
		state 	receive-chunk
	+comm>
		isa receive
		command "getMarker"
)

(p nothing-to-read
	=goal>
		isa 	goal
		state 	receive-chunk
	?comm>
		buffer	empty
	==>
	=goal>
		state 	fine
)
; (spp nothing-to-read :u -10) ;grants the production "receive-chunk" to be run all the time it's needed

(p receive-object
	=goal>
		isa 	goal
		state 	receive-chunk
	=comm>
		isa		object
	==>
	=goal>
		state 	fine
	-comm> ;store in dm
)

(p receive-marker
	=goal>
		isa 	goal
		state 	receive-chunk
	=comm>
		isa		marker
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



;(p kill-server
;	=goal>
;		isa 	goal
;		state 	fine
;	==>
;	=goal>
;		state 	stop
;	+comm>
;		isa		listener
;		turn	off
;)
	
(goal-focus goal)
)