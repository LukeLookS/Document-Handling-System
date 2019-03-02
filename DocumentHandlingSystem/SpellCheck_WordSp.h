#pragma once
/////////////////////////////////////////////////////////////////////
// SpellCheck_WordSp.h - check the spell and suggest right word    //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////
#include <iostream>  
#include <fstream>  
#include <string>  
#include <algorithm>  
#include <vector>
using namespace std;
const int ALPHABET_SIZE = 26; 

class TrieNode
{
public:
		std::string word; //store the words   
		bool isLeaf;
		TrieNode* children[ALPHABET_SIZE];  
};

class Trie
{
public:
		Trie();
		void insert(const char *str);//insert function used for insert new words
		int index_of(char str); // change the character into int value
		bool Search(const char* str);// search whether the word is exist return a bool value 
		vector<string> Suggestion(const char* str); // suggest ten word if user typr in word is not in the dictonary
		std::string autocomplete(Trie t); // auto execute the spell check function
private:
		TrieNode* pRoot;
		vector<string> Print(TrieNode* pRoot);
		vector<string> SuggestWord;
		int count;
};


// input the dictionary file to create trie 
Trie::Trie()
{
	pRoot = new TrieNode();
	ifstream file("dictionary.txt");
	std::string str;
	while (std::getline(file, str))
	this->insert(str.c_str()); // create the spell check dictonary
}

int Trie::index_of(char key) 
{
	int index = key - 'a';
	return index;
}

void Trie::insert(const char *key)
{
	TrieNode *tn = pRoot;
	for (unsigned level = 0; level < strlen(key); level++)
		{
			int index = index_of(key[level]);
			if (!tn->children[index])
				tn->children[index] = new TrieNode();
			tn = tn->children[index];
		}
	tn->word = key;
	// mark last node as leaf
	tn->isLeaf = true;
}

// search the word to judge whether the word is exist, if exist return true
bool Trie::Search(const char* str)
{
	int i = 0;
	int index = -1;
	TrieNode* pLoc = pRoot;
	while (pLoc && *str)
	{
		index = *str - 'a';
		if (index < 0) // if the character is upperword
			index = index + 32;
		if (index > ALPHABET_SIZE) // if the character is not word
			return false;
		pLoc = pLoc->children[index];
		str++; // move to next character
	}
	if (pLoc && pLoc->word != "")
		return true;
		return false;
}

// suggest the right word to user and return 10 word and store them into vector
vector<std::string> Trie::Suggestion(const char* str)
{
	int i = 0, index = -1;;
	TrieNode* pLoc = pRoot;
	count = 0; // use count to limit the return number of words
	vector<string> clear;
	SuggestWord = clear;
	while (pLoc && *str)
	{
		index = *str - 'a';
		if (index < 0)
			index = index + 32;
		if (pLoc->children[index] == NULL)
			return Print(pLoc);
		pLoc = pLoc->children[index];
			str++;
	}
	return Print(pLoc);
}

// find the suggest word
vector<std::string> Trie::Print(TrieNode* pRoot)
{
	TrieNode* pLoc = pRoot;
	if (NULL == pRoot)
		return SuggestWord;
	if (pLoc->isLeaf && count < 10)// && pLoc->isLeaf
	{
		//cout << pRoot->word << " " << endl;  //print the word of the suggestion
		SuggestWord.push_back(pLoc->word);
		count++;
	} 
	for (int i = 0; i < ALPHABET_SIZE; i++)
	Print(pRoot->children[i]);
	return SuggestWord;
}

// auto to find the wrong word and suggest the right word
std::string Trie::autocomplete(Trie t) {
	std::cout << "Type the word you intend to search" << endl;
	std::string str;
	vector<std::string> vtemp;
	cin >> str;
	bool isFind = t.Search(str.c_str());
	if (!isFind) 
	{
		std::cout << str << " is not in the dictonary \n";
		vtemp = t.Suggestion(str.c_str());
		std::cout <<"The suggestion word is: "<< vtemp[0];
		return vtemp[0];
	}
	else {
		std::cout << str << " is in the dictonary \n";
		return str;
	}
}