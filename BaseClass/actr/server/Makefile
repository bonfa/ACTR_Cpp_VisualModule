exec: 
	g++ server.cpp
	
ser:
	g++ -shared -fPIC server.cpp -o libserver.so -m32
	
clean:
	rm test.so libserver.so
