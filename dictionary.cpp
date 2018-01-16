#include "dictionary.h"

Dictionary::Dictionary(ADT structure)
{
	style = structure;
	//Allocation and intialization of root - same for both ADT
	char* ch = new char[2];
	ch[0] = char(0);
	ch[1] = '\0';

	Entry *head = (Entry*)malloc(sizeof(Entry));
	root = head;
	root->code = 0;
	root->frequency = 1;
	root->str = ch;
	root->left = NULL;
	root->right = NULL;
	numEntries = 0;
	threshold = 1000;
}

/* Empty Default constuctor - Constructor should be called with ADT specified */
Dictionary::Dictionary() {}

void Dictionary::put(char* key, int value, ADT structure)
{
	//Allcoate memory for the dictionary Entry and intialize variables
	char * copy = (char*)malloc(sizeof(char) * strlen(key) + 1);
	strcpy(copy, key);
	copy[strlen(key)] = '\0';

	Entry *nEntry = (Entry*)malloc(sizeof(Entry));
	nEntry->str = copy;
	nEntry->code = value;
	nEntry->frequency = 1;
	nEntry->left = NULL;
	nEntry->right = NULL;

	insert(nEntry, root, structure);
}

void Dictionary::insert(Entry *node, Entry *parent, ADT structure) {
	if (parent == NULL) return; //insertion to NULL will cause segmantation issues
	if (structure == e_BinaryTree) { // if a binary tree, recursively parse the tree and insert as a BST
		if (strcmp(node->str, parent->str) > 0) {
			if (parent->right == NULL) {
				parent->right = node;
				numEntries++;
			}
			else {
				//move down one layer and recursively insert
				insert(node, parent->right, structure);
			}
		}
		else if (strcmp(node->str, parent->str) < 0) {
			if (parent->left == NULL) {
				parent->left = node;
				numEntries++;
			}
			else {
				//move down one layer and recursively insert
				insert(node, parent->left, structure);
			}
		}
		else {
			//For debug purposes - based on the algorithm the same Entry should never be reinserted
			cout << "ERROR: REINSERT" << endl;
		}
	}
	else if (structure == e_LinkedList) { //structure as doubly linked list - insert acts as a push function to first node below the threshold
		numEntries++;
		Entry *pt = root; //if a linked list we iterate through rather than look recursively
		while (pt != NULL) {
			if (pt->frequency < threshold || pt->frequency < node->frequency) { //conditions for insert at earliest postition
				break;
			}
			pt = pt->right;
		}
		if (pt->left == NULL) { // at root
			pt->left = node;
			node->right = pt;
			root = node;
		}
		else if (pt->right == NULL) { // at tail
			pt->right = node;
			node->left = pt;
		}
		else { // in middle - doubly linked list so a few more pointer movements
			(pt->left)->right = node;
			node->left = pt->left;
			pt->left = node;
			node->right = pt;
		}
	}
	else {
		//in case non ADT specified 
		cout << "ERROR: Please specify correct method of insertion" << endl;
	}
}

void Dictionary::putInitial(char key, int value)
{
	//for intializeDictionary() allocate one ASCII character and place in dictionary
	char* ch = new char[2];
	ch[0] = key;
	ch[1] = '\0';
	put(ch, value, style);
}

int Dictionary::getfromChar(char* key, Entry *parent)
{
	//regular recursive traversal of binary tree
	if (parent == NULL) return -1; //not found
	if (strcmp(key, parent->str) == 0) {
		return parent->code;
	}
	else if (strcmp(key, parent->str) > 0) {
		return getfromChar(key, parent->right);
	}
	else {
		return getfromChar(key, parent->left);
	}
}

char* Dictionary::getfromInt(int key, Entry *parent) //lookup as doubly linked list with frequency analysis
{
	//all linked list traversals done are iterative
	Entry *pt = root;
	while (pt != NULL) {
		if (pt->code == key) {
			pt->frequency++; //update Entry usage frequency
			if (pt->frequency > threshold) {
				if (pt->frequency / threshold > 3) { //update threshold once max is 3 time larger than current threshold
					threshold = pt->frequency * 0.9; //reoffset threshold 
				}
				if (pt->right != NULL) {
					if ((pt->right)->frequency >= threshold) {
						return pt->str; //both the node and its next are over threshold, they are in the correct location
					}
				}
				//remove from list and reinsert
				if (pt->left == NULL) {}//already at head do nothing
				else if (pt->right == NULL) { // at end
					(pt->left)->right = NULL;
					pt->left = NULL;
					insert(pt, pt, e_LinkedList);
					return pt->str;
				}
				else { // in the middle
					(pt->left)->right = pt->right;
					(pt->right)->left = pt->left;
					pt->left = NULL;
					pt->right = NULL;
					insert(pt, pt, e_LinkedList);
					return pt->str;
				}
			}
			return pt->str;
		}
		pt = pt->right;
	}
	return '\0'; //interger not found
}

bool Dictionary::has_key(char* key, Entry *parent)
{
	//regular binary tree traversal
	if (parent == NULL) return false; //not found
	if (strcmp(key, parent->str) == 0) {
		return true;
	}
	else if (strcmp(key, parent->str) > 0) {
		return has_key(key, parent->right);
	}
	else {
		return has_key(key, parent->left);
	}
}

void Dictionary::reset ( Entry* head )
{
	if(head == NULL) return;
	if(style == e_LinkedList)
	{
		Entry* toDelete = head;
		Entry* nextDelete;
		while( toDelete )
		{
			nextDelete = toDelete->right;
			free(toDelete);
			toDelete = nextDelete;
		}
	}
	else if(style == e_BinaryTree)
	{
		if(head)
		{
			if(head->right) reset(head->right);
			if(head->left) 	reset(head->left);
			free(head);
		}
	}
	else
	{
		cerr << "ADT not specified for dictionary" << endl;
	}
	numEntries = 0;
}


void Dictionary::initalizeDictionary() {
	/* Empty dictionary if necessary */
	if(numEntries != 0)
	{
		reset();
	}
	for (int i = 1; i < 256; ++i)
		putInitial(char(i), i);
}

void Dictionary::printList() { //use for debug
	//Print list - if used with Binary Tree ADT... i dunno what will happen 
	Entry * pt = root;
	while (pt != NULL) {
		cout << pt->str << " " << pt->code << endl;
		pt = pt->right;
	}
}
