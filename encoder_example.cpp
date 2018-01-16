#include <iostream>

#include "encoder.h"

using namespace std;

/**
 *	encoder executable. 
 * 	usage: encode /path/to/input /path/to/output
 */
int main( int argc, char** argv ) {
	
	if(argc != 3)
		cerr << "Error: not enough arguements" << endl;
	
	Encoder e = Encoder(argv[1], argv[2]);
	e.encode();	

	cout << "Successfully encoded " << endl;
	return 0;
}