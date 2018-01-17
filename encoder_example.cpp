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
	
	Encoder e = Encoder();
	e.encode(argv[1], argv[2]);	

	cout << "Successfully encoded " << endl;
	return 0;
}
