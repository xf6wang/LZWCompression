#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Dictionary.h"

using namespace std;
class Encoder {
#define BUFFER_LIMIT 10000

public:
	/*Constructor*/
	Encoder(const char* inName, const char* outName);

	int numEntries; //number of entries - should be synchronized with numEntries in dictionary
	char* mainFile; //file that is read
	const char* outputName; //input file name
	const char* inputName; //output file name
	vector <int> result; //result vector of integers

	Dictionary dic; //dictionary

	/* Open a file and read as a stream, file stored in mainFile */
	void readFile(void);
	/* Outputs the numbers in binary format to output file */
	void toBinOut(void);
	/* Function to encode mainFile */
	void encode(void);
};