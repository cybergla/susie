#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cctype>
#include "InvertedIndex.h"
#include "DirTraverse.h"

#define SMALLEST_WORD 2		//for trivial words like is, in, to etc../
#define LARGEST_WORD  46	//largest word in dictionary is 45 letters long

using namespace std;

InvertedIndex index;

bool isCommon(char *buf)
{
	if (!strcmp(buf, "the") || 
		!strcmp(buf, "for") || 
		!strcmp(buf, "and") || 
		!strcmp(buf, "you") || 
		!strcmp(buf, "with") || 
		!strcmp(buf, "its") || 
		!strcmp(buf, "his") ||
		!strcmp(buf, "hers") ||
		!strcmp(buf, "they") ||
		!strcmp(buf, "their") ||
		!strcmp(buf, "that") ||
		!strcmp(buf, "have") ||
		!strcmp(buf, "your") ||
		!strcmp(buf, "who") ||
		!strcmp(buf, "not"))
		return true;
	else
		return false;
}

void parse(string path)
{
	fstream fin;
	char buf[100];
	fin.open(path.c_str(), ios::in);
	while (fin >> buf)
	{
		size_t i;
		for ( i = 0; buf[i] != '\0';)
		{
			if (buf[i] >= 'A' && buf[i]<= 'Z'   )		//capitals
			{
				buf[i] += 32;							//convert to lowercase
				i++;
			}
			else if (buf[i] >= 'a' && buf[i] <= 'z')
			{
				i++;									
			}
			else if (buf[i] >= '0' && buf[i] <= '9')		//numbers
			{
				i++;
			}
			else
			{
				for (size_t j = i; buf[j] != '\0'; j++)			//remove special chars
					buf[j] = buf[j + 1];
			}
		}
		if (*buf != '\0'  && i > SMALLEST_WORD && i < LARGEST_WORD && !isCommon(buf))
		{
			index.add(string(buf),path);
		}
	}
	fin.close();
}

int main(int argc, char* argv[])
{
	DirTraverse tdir;
	string root;
	Node *word;
	if (argv[1]==NULL ) 
		root = "C:\\users\\tanay\\documents\\test";
	else
		root = string(argv[1]);

	tdir.getPaths(root);
	
	for (size_t i = 0; i < tdir.docPaths.size(); i++)
	{
		parse(tdir.docPaths[i]);
	}

	ofstream fout;
	fout.open("index.dat", ios::binary);
	if (fout.fail() == true) cout << "failed to open";
	fout.write((char*)&index, sizeof(InvertedIndex));
	
	
	cout << "\n";
	system("pause");
	return 0;
}