ENCODER='encode'
DECODER='decode'

all:
	make encoder
	make decoder
encoder:
	g++ -o $(ENCODER) encoder_example.cpp encoder.cpp dictionary.cpp
	
decoder:
	g++ -o $(DECODER) decoder_example.cpp decoder.cpp dictionary.cpp
	
clean:
	rm $(ENCODER) $(DECODER) *.bin 
