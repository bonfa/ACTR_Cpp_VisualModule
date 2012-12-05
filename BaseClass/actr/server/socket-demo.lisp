(clear-all)
(define-model test-nxt-motor
    
(chunk-type goal state)
(add-dm (goal ISA goal))

(p start
	=goal>
   		ISA goal
   		state nil
   	==>
   	=goal>
   		state back
   	+comm>
		isa		listener
		turn	on)

(p wait
	=goal>
	isa goal
	state back
	?comm>
		state	free
	==>
	+comm>
		isa goal
		state	nil
	=goal>
		state	fine)

(p start-reading
	=goal>
		isa 	goal
		state 	start-reading
	==>
	=goal>
		state 	receive-chunk
	+comm>
		isa receive
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

(p receive-chunk
	=goal>
		isa 	goal
		state 	receive-chunk
	=comm>
		isa			goal
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