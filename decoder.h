#ifndef _DECODER_H_
#define _DECODER_H_

#include <iostream>
#include <fstream>
#include <string>

#include "dictionary.h"

class Decoder {
public:
	Decoder();

	/**
	 * 	Decodes binary input file
	 *
	 * 	inputFile: binary file containing compressed file
	 * 	outputFile: name given to decompressed file
	 */ 
	void decode( const char *inputFile, const char *outputFile );
	
private:
	int size; 				/* size of binary file */
	int numEntries; 		/* number of dictionary entries */
	int *codes; 			/* codes from binary file */
	const char *inFile; 	/* input file name */
	const char *outFile; 	/* output file name */
	
	ofstream ofs; 			/* stream for reading in binary file */

	/**
	 * Opens inFile and determines the number of bytes stored in the file 
	 */
	int fileSize( void );
	
	/** 
	 * Opens file and reads file as a stream 
	 */
	void readFile( void );
	
protected:
	Dictionary dic; 		/* dictionary used to store code values */
};

#endif /* _DECODER_H_ */