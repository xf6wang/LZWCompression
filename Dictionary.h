#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <string>
#include <vector>

using namespace std;
class Dictionary {
public:
	/*structure for binary tree/linked list the pointer logic is different but the struct is the same! */
	struct entry {
		char * str;
		int code;
		int frequency;
		entry *left;
		entry *right;
	};

	/* ENUM allows for the selection of how the dictionary entries are to be stored */
	enum ADT {
		e_BinaryTree,
		e_LinkedList //doubly linked list
	};

	/*Constructor(s)*/
	Dictionary();
	Dictionary(ADT structure);

	int threshold; //this is used for frequency analysis when stored as a linked list
	int numEntries; //number of entries in dictionary
	ADT style; //0 if to be stored as a binary tree 1 if to be stored as a doubly linked list

	entry *root; 

	/* Intialize the dictionary with all ASCII characters */
	void initalizeDictionary(void);
	/* insert an entry into the dictionary - caller must allocate memory */
	void insert(entry *node, entry *parent, ADT structure);
	/* Fuction allocates memory for an entry an calls insert */
	void put(char* key, int value, ADT structure);
	/* Helper function for intializeDictionary() - should not be used elsewhere*/
	void putInitial(char key, int value);
	/* Query structure for integer given character - used for encoding */
	int getfromChar(char* key, entry *parent);
	/* Query structure for character given interger - used for decoding */
	char* getfromInt(int key, entry *parent);
	/* True/False if key exists in dictionary already */
	bool has_key(char* key, entry *parent);
	/* Print list - only to be used if structure is a linked list */
	void printList(void);
};
