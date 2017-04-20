#pragma once

#include<iostream>
#include<string>


class Node
{
	size_t wordHash;
	int frequency;

public:
	std::vector<std::string> paths;
	Node *next;

	Node()
	{
		wordHash = 0;
		next = NULL;
		frequency = 0;
	}

	void setData(size_t wordHash, int freq, std::string path)
	{
		this->wordHash = wordHash;
		this->frequency = freq;
		this->paths.push_back(path);
	}

	void incFrequency()
	{
		frequency++;
	}

	size_t getHash()
	{
		return wordHash;
	}

	bool checkHash(size_t pHash)
	{
		return pHash == wordHash;
	}

	int getFrequency()
	{
		return frequency;
	}
};
