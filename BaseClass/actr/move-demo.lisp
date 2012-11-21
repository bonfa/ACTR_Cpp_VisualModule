(clear-all)
(define-model test-nxt-motor
    
    ; (sgp :r-engine #\b :l-engine #\c)
	(chunk-type goal state)
	(add-dm (goal ISA goal))
    
    (p start
       =goal>
	   ISA goal
       state nil
       ==>
	   =goal>
	   state back
	   +nxt-cv>
	   		isa		play-demo)

	(p wait
		=goal>
		isa goal
		state back
		?nxt-cv>
			state	free
		=nxt-cv>
			isa play-demo
		-	int 10
		==>
		!output! "sbagliato"
		=goal>
			state	cacca)
		
	(p back
		=goal>
		isa goal
		state back
		?nxt-cv>
			state	free
		=nxt-cv>
			isa play-demo
			int 10
		==>
		!output! "giusto"
		=goal>
		state asdsg)
		
(goal-focus goal)
)