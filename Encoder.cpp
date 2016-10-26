#include "Encoder.h"

Encoder::Encoder(const char* inName, const char* outName)
{
	dic = Dictionary(dic.e_BinaryTree);
	dic.initalizeDictionary();
	inputName = inName;
	outputName = outName;
	numEntries = 256;
}

void Encoder::readFile()
{
	ifstream inFile(inputName);
	string nxtLine = string("");
	string fullDoc;
	while (getline(inFile, nxtLine)) {
		fullDoc += nxtLine;
		fullDoc += '\n';
	}

	char *c = new char[fullDoc.size() + 1];
	copy(fullDoc.begin(), fullDoc.end(), c);
	c[fullDoc.size()] = '\0';
	mainFile = c;
	inFile.close();
	cout << "FILE READ" << endl;
}

void Encoder::encode()
{
	readFile();
	int i = 0;
	char cur[BUFFER_LIMIT];
	cur[0] = mainFile[0];
	cur[1] = '\0';
	char ch = mainFile[0];
	while (mainFile[i + 1] != '\0')
	{
		int ovflw = 0;
		while (dic.has_key(cur, dic.root) && ch != '\0') //keep going until longest string found
		{
			ovflw++;
			ch = mainFile[++i];
			if (ovflw > BUFFER_LIMIT) break; // avoid array overflow - unlikely 10000 characters repeating anyways
			cur[ovflw] = ch;
			cur[ovflw + 1] = '\0';
		}
		if (ch == '\0') break;
		dic.put(cur, numEntries++, dic.e_BinaryTree);
		char last = cur[ovflw];
		cur[ovflw] = '\0'; //terminate string here to get rid of last letter
		result.push_back(dic.getfromChar(cur, dic.root));
		cur[0] = last;
		cur[1] = '\0'; //reset the current input
	}
	result.push_back(dic.getfromChar(cur, dic.root));
	toBinOut();
}


void Encoder::toBinOut()
{
	int* resultpt = &result[0];
	fstream binaryIo;
	binaryIo.open(outputName, ios::out | ios::binary | ios::trunc);
	binaryIo.seekp(0);
	binaryIo.write((char*)resultpt, result.size() * sizeof(resultpt[0]));
	binaryIo.seekp(0);
	binaryIo.close();
}
