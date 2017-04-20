#pragma once

#include"Node.h"
#include<functional>
#include<vector>


#define SIZE_OF_ARRAY 10007

class InvertedIndex
{
	Node* ListofNodes[SIZE_OF_ARRAY];
	std::hash<std::string> str_hash;
	size_t hash, index;

public:
	InvertedIndex()
	{
		Node* notfound;
		notfound = new Node;
		for (int i = 0; i < SIZE_OF_ARRAY; i++)
		{
			ListofNodes[i] = notfound;
		}
	}

	int add(std::string word, std::string path)			//adds word to the index
	{
		hash = str_hash(word);
		index = hash % SIZE_OF_ARRAY;
		if (ListofNodes[index]->getHash() == 0)
		{
			ListofNodes[index] = new Node;
			ListofNodes[index]->setData(hash, 1, path);
			return 1;
		}
		else										//collision
		{
			Node *it = ListofNodes[index];
			while (it!=NULL)
			{
				if (it->checkHash(hash))			//same word
				{
					it->incFrequency();
					return 2;
				}
				it = it->next;
			} 
			it = ListofNodes[index];
			while (it->next != NULL)it = it->next;  //to point it to the last node
													//separate chaining
			Node *newNode = new Node;
			newNode->setData(hash, 1, path);
			it->next = newNode;
			return 3;

		}
		return 0;
	}

	Node *retrieve(std::string word)
	{
		hash = str_hash(word);
		index = hash % SIZE_OF_ARRAY;

		if (ListofNodes[index]->getHash() == 0)
		{
			return NULL;
		}
		else
		{
			if (ListofNodes[index]->checkHash(hash))
			{
				return ListofNodes[index];
			}
			else
			{
				Node *it = ListofNodes[index];
				while (it!=NULL)
				{
					if (it->checkHash(hash))
					{
						return it;
					}
					it = it->next;
				}
			}
		}
		return NULL;
	}
};