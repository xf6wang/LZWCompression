#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Dictionary.h"

using namespace std;
class Decoder {
public:
	/*Constructor*/
	Decoder(const char *inputFile, const char *outputFile);

	int size; //binary file size
	int numEntries; //number of dictionary entries
	int *codes; //array of ints retrieved from binary file
	const char *inFile; //input file name 
	const char *outFile; //output file name

	ofstream ofs; //stream for reading in binary file

	Dictionary dic; //instance of dictionary class

	/* Opens inFile and determines the number of bytes stored in the file */
	int fileSize(void);
	/* Opens file and reads file as a stream */
	void readFile(void);
	/* Decodes binary file into txt file TODO: add parser for encoding & decoding to allow for image inputs */
	void decode(void);
};
