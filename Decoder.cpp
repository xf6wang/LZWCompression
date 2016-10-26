#include "Decoder.h"

Decoder::Decoder(const char *inputFile, const char *outputFile)
{
	dic = Dictionary(dic.e_LinkedList); //must store file as linked list for decoding
	dic.initalizeDictionary();
	inFile = inputFile;
	outFile = outputFile;
	numEntries = 256; //offset to account for initial dictionary ASCII inputs
	ofs = ofstream(outputFile, ios::app);
}

void Decoder::readFile()
{
	size = fileSize();
	size = size / 4; //size is returned as number of bytes, must divide by 4 to determine correct array size
	codes = (int*)malloc(sizeof(int) * size); //allocate memory for list of compressed integers
	ifstream binaryI;
	binaryI.open(inFile, ios::binary);
	binaryI.clear();
	binaryI.seekg(0, ios::beg);
	if (binaryI.is_open()) {
		binaryI.read((char*)codes, size * sizeof(codes[0]));
		binaryI.close();
	}
	else {
		cout << "ERROR: UNABLE TO READ FILE" << endl;
	}
}

int Decoder::fileSize() {
	std::ifstream mySource;
	mySource.open(inFile, std::ios_base::binary);
	mySource.seekg(0, std::ios_base::end);
	int size = mySource.tellg();
	mySource.close();
	return size;
}

void Decoder::decode()
{
	readFile();
	int cur, next = 0;
	cur = codes[0];
	for (int i = 1; i < size; i++)
	{
		next = codes[i];

		//get the current decompressed string and the next one
		char* curpt = dic.getfromInt(cur, dic.root);
		char* nxtpt = dic.getfromInt(next, dic.root);

		//allocate memory for this string
		char* curCode = (char*)malloc(sizeof(char) * strlen(curpt) + 1);
		strcpy(curCode, curpt);
		curCode[strlen(curpt)] = '\0';

		//reallocate memory - suspect that due to race conditions, sometimes curCode prematurely changed causes weird errors - this is to be safe
		int len = strlen(curCode);
		char* newEntry = (char*)malloc(sizeof(char) * strlen(curpt) + 2);
		strcpy(newEntry, curCode);

		//create a new dictionary entry to mirror encoded dictionary
		if (nxtpt != '\0') {
			char* nxtCode = (char*)malloc(sizeof(char) * strlen(nxtpt) + 1);
			strcpy(nxtCode, nxtpt);
			nxtCode[strlen(nxtpt)] = '\0';
			newEntry[len] = nxtCode[0];
			newEntry[len + 1] = '\0';
		}
		else {
			//this is in the case of cScSc where there will be an unknown entry - we need to append the string differently
			newEntry[len] = curCode[0];
			newEntry[len + 1] = '\0';
		}

		ofs << curpt; //write to file

		//insert into dictionary
		dic.put(newEntry, numEntries++, dic.e_LinkedList); 
		cur = next;
	}
	int end = codes[size - 1];
	ofs << dic.getfromInt(end, dic.root);
	ofs.close();
}

