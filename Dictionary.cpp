#include "Dictionary.h"

/* OPTIMIZATIONS:
 * All optimzations are done in the storage of data. The core compression algorithm is efficient. The most expensive operations are in the search and insertion of entries
 * In the non-optimized manner, the ADT is simply a linked list. Insertion is a push operation so it is O(1) however the lookup is much more costly. On average, lookup is O(N)
 * but for the LZW algorithm, it must be ensured at each dictionary entry is unique. Thus, when searching for the longest string that is not in the dictionary, the list must 
 * be traversed a number of times including one time where the entire list is traversed to ensure the entry does not exist. This is done quite frequently and as the dictionary 
 * becomes larger due to more entry insertions, the lookup time is extremely expensive. 
 *
 * Optimization 1: Binary Tree for encoding
 * Storing the dictionary entires as a Binary Tree rather than a linked list reduces the lookup time but increases the insertion time.
 * However, given how costly the lookup is for a linked list, the increased insertion times are welcome. This binary tree is unqiue in that due to the way
 * the intial dictionary was inserted, it begins effectively as a splay tree rather and a balanced BST. However, after running emperical tests, balancing the intial dictionary 
 * does not have large benefits due to the overall number of entries. Thus, since no balancing was done, we can think of this tree as a linked list of binary trees!
 * Why? The inital splay tree is effectively a linked list. Now we take an entry (ie. "He") we traverse until we hit "H" at which point we go one further (strcmp("H", "He") will be  < 0) 
 * because a character is valued higher than a null character. We get to "I" where we find "He" is less than "I" and thus inserted. The next time something (ie."Hel") approaches,
 * it will reach the "He" node and be appended. We can see that as the number of entries increases (given large text and image documents they will be fairly random) we effectively have a small BST for
 * each ASCII character, a linked list of binary trees! Lookup is much faster because we only need to look at 1/256 of the dictionary entries in one go (actually less because each BST can be traversed quickly as well)
 * Now, both lookup and insertion are Θ(log n) operations. This reduces the encoding time from hours to under 1 second. 
 *
 * Optimization 2: Frequency analysis of doubly linked list for decoding 
 * 
 */


Dictionary::Dictionary(ADT structure)
{
	style = structure;
	//Allocation and intialization of root - same for both ADT
	char* ch = new char[2];
	ch[0] = char(0);
	ch[1] = '\0';

	entry *head = (entry*)malloc(sizeof(entry));
	root = head;
	root->code = 0;
	root->frequency = 1;
	root->str = ch;
	root->left = NULL;
	root->right = NULL;
	numEntries = 0;
	threshold = 1000;
}

/*Empty Default constuctor - Constructor should be called with ADT specified */
Dictionary::Dictionary() {}

void Dictionary::put(char* key, int value, ADT structure)
{
	//Allcoate memory for the dictionary entry and intialize variables
	char * copy = (char*)malloc(sizeof(char) * strlen(key) + 1);
	strcpy(copy, key);
	copy[strlen(key)] = '\0';

	entry *nEntry = (entry*)malloc(sizeof(entry));
	nEntry->str = copy;
	nEntry->code = value;
	nEntry->frequency = 1;
	nEntry->left = NULL;
	nEntry->right = NULL;

	insert(nEntry, root, structure);
}

void Dictionary::insert(entry *node, entry *parent, ADT structure) {
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
			//For debug purposes - based on the algorithm the same entry should never be reinserted
			cout << "ERROR: REINSERT" << endl;
		}
	}
	else if (structure == e_LinkedList) { //structure as doubly linked list - insert acts as a push function to first node below the threshold
		numEntries++;
		entry *pt = root; //if a linked list we iterate through rather than look recursively
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

int Dictionary::getfromChar(char* key, entry *parent)
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

char* Dictionary::getfromInt(int key, entry *parent) //lookup as doubly linked list with frequency analysis
{
	//all linked list traversals done are iterative
	entry *pt = root;
	while (pt != NULL) {
		if (pt->code == key) {
			pt->frequency++; //update entry usage frequency
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

bool Dictionary::has_key(char* key, entry *parent)
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

void Dictionary::initalizeDictionary() {
	for (int i = 1; i < 256; ++i)
		putInitial(char(i), i);
}

void Dictionary::printList() { //use for debug
	//Print list - if used with Binary Tree ADT... i dunno what will happen 
	entry * pt = root;
	while (pt != NULL) {
		cout << pt->str << " " << pt->code << endl;
		pt = pt->right;
	}
}