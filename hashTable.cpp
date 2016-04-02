//Yuyang Lu
//yl5pw
//3.17.2016
//hashTable.cpp

#include "hashTable.h"

using namespace std;

hashTable::hashTable(int size) {
	v.resize(size);
	for (int i = 0; i < v.size(); i++) {
		v[i] = "";
	}
	lastEntry = "";
	lastHash = 0;
}

hashTable::~hashTable() {
}

void hashTable::insert(string s) {
	/*v[hash(s)]->push_back(s);*/
	int hash = hashFunction(s) % v.size();
	int i = 1;
	while (v[hash] != "") {
		hash = (hash+i^2) % v.size();
		i++;
	}
	v[hash]=s;
	lastEntry = s;

	/*else {
		int newHash = h.size() - hash(s);
		for (int i=1; i < MAX_SIZE; i++) {
			if (v[hash(s)+i*newHash].empty()) {
				v[hash(s)+i*newHash]->push_back(s);
				break;
			}
		}
	}
	else {
		v[hash(s)].push_back(s);
	}*/
}

bool hashTable::find(string s) {
	/*for (list<string>::iterator it = v[hash(s)]->begin(); it != v[hash(s)]->end(); it++) {
		if (s == *it) {
			return true;
		}
	}
	return false;*/
	int hash = hashFunction(s) % v.size();
	int i = 1;
	while (v[hash] != "" && v[hash] != s) {
		hash = (hash+i^2) % v.size();
		i++;
	}
	if (v[hash] == "")
		return false;
	else
		return true;
}

unsigned int hashTable::hashFunction(string s) {
	unsigned int value = 0;
	if (s.length() > lastEntry.length() && s.substr(0,lastEntry.length())==lastEntry) {
		value = lastHash;
		for (int i = lastEntry.length(); i < s.length(); i++) {
			value = value + s[i]*(37^i);
		}
	}
	else {
		for (int i = 0; i < s.length(); i++) {
		//value = value + s[i];
		value = value + s[i]*(37^i);
		}
	}
	lastHash=value;
	return value;
}

