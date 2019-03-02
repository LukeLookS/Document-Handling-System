#pragma once
/////////////////////////////////////////////////////////////////////
// DocumentR.h - key/value pair store the document                 //
// Mengjie Shi                                                     //
// SUID: 457056896                                                 //
/////////////////////////////////////////////////////////////////////
#include <unordered_map>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <iostream>

using Key = std::string;
using Keys = std::vector<Key>;

// element class used for store the elemet
class Element
{
public:
	Element() {}
	std::string key; // key
	std::vector<std::string> filenames;   // filename
	std::string show(std::string); // show all element in the hashtable
};

std::string Element::show(std::string str)
{
	std::ostringstream out;
	out.setf(std::ios::adjustfield, std::ios::left);
	std::vector<std::string> filenames_ = static_cast<std::vector<std::string>>(filenames);
	if (filenames_.size() > 0){
		out << "" << std::setw(8) << "filenames are: ";
		for (size_t i = 0; i < filenames_.size(); ++i){
			out << filenames_[i];
			if (i < filenames_.size() - 1)
				out << ", ";
		}
	}
	else {
		out << str << " is not in the table";
	}
	out << "\n";
	return out.str();
}

// use the documentStore class to store all of the element
class DocumentStore
{
public:
	using Key = std::string;
	using Keys = std::vector<Key>;
	Keys keys();
	bool hasKey(Key key);
	bool saveRecord(Key key, Element elem);
	size_t count();
	Element value(Key key);
	unsigned FindVa(std::vector<std::string> v, std::string target);
private:
	using Item = std::pair<Key, Element>;
	std::unordered_map<Key, Element> store;
};

DocumentStore::Keys DocumentStore::keys(){
	Keys keys;
	for (Item item : store)
	keys.push_back(item.first);
	return keys;
}

bool DocumentStore::hasKey(Key key)
{
	if (store.find(key) == store.end())
		return false;
	return true;
}

bool DocumentStore::saveRecord(Key key, Element elem)
{
	if (FindVa(store[key].filenames, elem.filenames[0]) != 0)
		return false;
	if (store.find(key) != store.end())
		store[key].filenames.push_back(elem.filenames[0]);
	else
		store[key] = elem;
	return true;
}


Element DocumentStore::value(Key key)
{
	if (store.find(key) != store.end())
		return store[key];
	return Element();
}

size_t DocumentStore::count()
{
	return store.size();
}

unsigned DocumentStore::FindVa(std::vector<std::string> v, std::string target)
{
	if (v.size() == 0)  
		return 0;
	unsigned c;
	for (c = 0; c < v.size(); c++){
		if (v[c] == target){
			c++;  
			break;
		}
	}
	if (v[c - 1] != target)
		return 0;  
	return c;  
}

