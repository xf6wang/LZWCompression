#include <iostream>

#include "decoder.h"

using namespace std;

/**
 *	decoder executable. 
 * 	usage: decode /path/to/input /path/to/output
 */
int main( int argc, char** argv ) {
	
	if(argc != 3)
		cerr << "Error: not enough arguements" << endl;
	
	Decoder d = Decoder();
	d.decode(argv[1], argv[2]);	

	cout << "Successfully decoded " << endl;
	return 0;
}
