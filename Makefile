all:
	g++ -o dictionary.o dictionary.cpp
	g++ encode encoder.cpp dictionary.o
	g++ decode decoder.cpp dictionary.o

encoder:
	g++ encode encoder.cpp dictionary.o
	
decoder:
	g++ decode decoder.cpp dictionary.o
	
clean:
	rm *.o encode decode