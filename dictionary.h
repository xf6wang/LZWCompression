#ifndef _DICTIONARY_H_
#define _DICTIONARY_H_

#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>

using namespace std;
class Dictionary {
public:
	/**
	 * Structure for binary tree and linked list 
	 * Different pointer logic but same struct
	 */
	typedef struct Entry {
		char * str;
		int code;
		int frequency;
		Entry *left;
		Entry *right;
	};

	/**
	 * Allows for the selection of how the dictionary entries are to be stored 
	 */
	enum ADT {
		e_BinaryTree,
		e_LinkedList 			/* doubly linked list */
	};

	Dictionary( void );
	Dictionary( ADT structure );

	/**
   	 * Intialize the dictionary with all ASCII characters 
	 */
	void initalizeDictionary( void );

	/** 
	 * Fuction allocates memory for an Entry an calls insert */
	void put( char* key, int value, ADT structure );

	/**
	 * Encoding: 
     * Query structure for code given string  
	 */
	int getfromChar( char* key, Entry *parent );
	
	/** 
	 * Decoding:
	 * Query structure for string given code
	 */
	char* getfromInt( int key, Entry *parent);
	
	void printList( void );
	
	bool has_key( char* key, Entry *parent );
	
private:
	int threshold; 				/* used for frequency analysis when stored as a linked list */
	int numEntries; 			
	ADT style; 					/* 0 if to be stored as a binary tree 1 if to be stored as a doubly linked list */

	Entry *root; 				/* first entry */
	
	/**
   	 * Insert an Entry into the dictionary - caller must allocate memory 
	 */
	void insert( Entry *node, Entry *parent, ADT structure );
	
	/**
     * Helper function for intializeDictionary()
	 */
	void putInitial( char key, int value );
	
	/**
	 * Empty the contents of the dictionary.
	 * Needs to be done each time a file is to be encoded/decoded.
	 *
	 * Takes in a pointer so binary tree deletion can be done recursively
	 */ 
	void reset( Entry* head );
};

#endif /* _DICTIONARY_H_ */
