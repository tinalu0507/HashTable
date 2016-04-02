//Yuyang Lu
//yl5pw
//3.17.2016
//hashTable.h

#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <iterator>

using namespace std;

class hashTable {
public:
	hashTable(int size);
	~hashTable();
	void insert(string s);
	bool find(string s);
	unsigned int hashFunction(string s);

private:
	vector<string> v;
	string lastEntry;
	int lastHash;
};

#endif