#include "Encoder.h"
#include "Decoder.h"
#include <time.h>
#include "Dictionary.h"

int main() {
	/* MAIN FILE - gives example of how to use the encoder and decoder */
	clock_t t1, t2;
	t1 = clock();
	Encoder e = Encoder("input.txt", "example.bin");
	e.encode();	
	cout << "FILE ENCODED" << endl;  
	Decoder d = Decoder("example.bin", "out.txt");
	d.decode();
	cout << "FILE DECODED" << endl;
	t2 = clock();
	float diff((float)t2 - (float)t1);
	cout << diff/CLOCKS_PER_SEC << endl; 

	system("pause");
	return 0;
}