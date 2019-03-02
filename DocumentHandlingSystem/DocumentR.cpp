/////////////////////////////////////////////////////////////////////
// DocumentR.cpp - key/value pair store the document               //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////
#include "DocumentR.h"
#include "SpellCheck_WordSp.h"
#include <iostream>  
#include <fstream>  
#include <string>  
#include <algorithm>  
#include <vector>

using namespace std;

// eleminate the symbol in the text file
std::string Eliminatesymbol(const char* str, int maxnum) {
	std::string strr;
	for (unsigned level = 0; level < strlen(str); level++)
	{
		int indexs = str[level] - 'a';
		int indexb = str[level] - 'A';
		if ((indexs >= 0 && indexs <= maxnum) || (indexb >= 0 && indexb <= maxnum))
			strr += str[level];
		else {
			continue;
		}
	}
	return strr;
}

// use the split function to split the input text
void split(const std::string &s, char delim, vector<std::string> &elems) {
	string temp;
	for (size_t i = 0; i < s.size(); i++)
	{
		if (s.at(i) != delim)
		{
			temp.append(s, i, 1);
			if (i == s.size() - 1) {
				temp = Eliminatesymbol(temp.c_str(), 25);
				if (temp != "")
					elems.push_back(temp);
			}
		}
		else if (temp != "")
		{
			temp = Eliminatesymbol(temp.c_str(), 25);
			if (temp != "")
				elems.push_back(temp);
			temp = "";
		}
	}
}

// change the int to string
std::string intToString(int a)
{
	std::stringstream ss;
	ss << a++;
	return ss.str();
}

// retrive the document
DocumentStore Document_Retrive(unsigned filenum) {
	DocumentStore doc;
	for (size_t num = 0; num < filenum; num++)
	{
		std::string fullname = "./FileSet/" + intToString(num) + ".txt";
		std::string filename = intToString(num) + ".txt";
		std::ifstream file(fullname);
		std::string str;
		std::vector<std::string> elems;
		while (std::getline(file, str))
			split(str, ' ', elems);

		int count = 0;
		std::string su;
		for (unsigned i = 0; i < elems.size(); i++)
		{
			su = elems[i].c_str();
			Element temp;
			temp.key = su;
			temp.filenames.push_back(filename);
			doc.saveRecord(temp.key, temp);
		}
	}
	return doc;
}

int main() {
	std::cout << "     Tire function Prove" << std::endl;
	std::cout << "=============================\n";
	Trie t;
	vector<std::string> elems1;
	std::string str1;
	std::cout << "Test the TobeSpellChecked.txt\n\n";
	ifstream text("TobeSpellChecked.txt");
	while (std::getline(text, str1)) {
		split(str1, ' ', elems1);
	}
	vector<vector<std::string>> vtemp;
	vector<std::string> wrongword;
	// test the spell check function is right 
	int correct = 0;
	for (unsigned i = 0; i < elems1.size(); i++) {
		bool isFind = t.Search(elems1[i].c_str());
		if (!isFind) {
			wrongword.push_back(elems1[i]);
			vtemp.push_back(t.Suggestion(elems1[i].c_str()));
		}
	}
	int i = 0;
	for (auto k : vtemp) {
			std::cout <<" Wrong word: " <<wrongword[i] << endl;
			std::cout << " Right word suggestion shows below " << endl << "( ";
			for (auto a : k)
				std::cout << a << " ";
			std::cout << ")\n\n";
			i++;
	}
	cout << endl;
	std::cout << "     Document Retrivel" << std::endl;
	std::cout << "=============================\n";
	std::cout << "Test to just retrivel 10 files in fileset" << std::endl;
	std::cout << "Wait to generate hashtable..." << std::endl << std::endl;
	DocumentStore doc = Document_Retrive(10);
	string str;
	str = t.autocomplete(t);
	std::cout << doc.value(str).show(str);

	/*Keys keys = doc.keys();
	for (Key key : keys)
	{
		std::cout << "\n  " << key << ":";
		std::cout << doc.value(key).show();
	}*/

	std::cout << "Size of the table is " << doc.count() << "\n\n";
	std::cout << "Test to retrivel 4938 files in fileset" << std::endl;
	std::cout << "Wait to generate hashtable..." << std::endl << std::endl;
	DocumentStore doc1 = Document_Retrive(4938);
	string str5;
	str5 = t.autocomplete(t);
	std::cout << doc1.value(str5).show(str5);
	system("pause");
}