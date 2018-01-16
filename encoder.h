#ifndef _ENCODER_H_
#define _ENCODER_H_

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "dictionary.h"

#define BUFFER_LIMIT 10000

using namespace std;
class Encoder {
public:
	Encoder();

	/**
	 * 	Encode file to binary format
	 *
	 * 	inName: uncompressed file
	 * 	outName: binary compressed file name 
	 */ 
	void encode( const char* inName, const char* outName );
	
private:
	int numEntries; 			/* number of entries */
	
	const char* outputName; 	/* input file name */
	const char* inputName; 		/* output file name */
	vector <int> result; 		/* result vector of integers */

	/** 
	 * Open a file and read as a stream, file stored in mainFile 
	 */
	void readFile( void );
	/**
	 * Outputs the numbers in binary format to output file 
	 */
	void toBinOut( void );
	
protected:
	Dictionary dic; 			/* dictionary */
	char* mainFile; 			/* file to be compressed */
};

#endif /* _ENCODER_H_ */
