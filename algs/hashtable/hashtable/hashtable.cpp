// hashtable.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <iostream>
#include <assert.h>
using namespace std;
const int DEFAULT_SIZE = 8;
const float MAX_ALPHA = 0.75;
const int GROW_FACTOR = 2;


int Hash(const string& data, int tablesize) {
	int hash = 0;
	for (unsigned int i = 0; i < data.size(); i++) {
		hash = (hash * 127 + data[i]) % tablesize;
	}
	return hash  % tablesize;
}
int Hash2(const string& data, int tablesize) {
	int hash = 0;
	for (unsigned int i = 0; i < data.size(); i++) {
		hash = (hash * 197 + data[i]) % tablesize;
	}
	return (hash*2+1) % tablesize;
}


template < class T>
class HashTable {
public:
	HashTable(const T& nil, const T& del, int size = DEFAULT_SIZE);

	~HashTable();


	bool Has(const T& key);
	bool Add(const T& key);
	bool Delete(const T& key);


private:
	vector<T> table;
	int keysCount;
	void growTable();
	const T DEL;
	const T NIL;
};

template < class T>
HashTable<T>::HashTable(const T& nil, const T& del, int size) :
	
	keysCount(0) ,
	DEL(del),
	NIL(nil)
{
	assert(size > 0);
	table.resize(size, NIL);

}

template < class T>
HashTable<T>::~HashTable()
	
{
	table.clear();
	
}

template < class T>
bool HashTable<T>::Has(const T& key) {
	int hash = Hash(key, table.size());
	int hash2 = Hash2(key, table.size());
	int stepsCount = 0;
	while (table[hash] != NIL && stepsCount < table.size()) {
		stepsCount++;
		if (table[hash] == key) {
			
			return true;
		}
		
		hash = (hash + hash2) % table.size();
	}




	return false;
}


template < class T>
bool HashTable<T>::Add(const T& key) {
	if ((float)keysCount / (float)table.size() >= MAX_ALPHA)
		growTable();
	int hash = Hash(key, table.size());
	int hash2 = Hash2(key, table.size());
	int firstDelPos = -1;
	int stepsCount = 0;
	while (table[hash] != NIL && stepsCount < table.size()) {
		stepsCount++;
		if (table[hash] == DEL && firstDelPos == -1)
			firstDelPos = hash;

		if (table[hash] == key)
			return false;
		hash = (hash + hash2)%table.size();
	}
	if (firstDelPos != -1)
	{
		table[firstDelPos] = key;
		
	}
	else {
		table[hash] = key;
	}
	
	
	keysCount++;
	return true;
}


template < class T>
bool HashTable<T>::Delete(const T& key) {
	int hash = Hash(key, table.size());
	int hash2 = Hash2(key, table.size());
	int stepsCount = 0;
	while (table[hash] != NIL && stepsCount < table.size()) {
		stepsCount++;
		if (table[hash] == key) {
			table[hash] = DEL;
			keysCount--;
			return true;
		}
		
		hash = (hash + hash2) % table.size();
	}
		
	
	
	
	return false;
}


template < class T>
void HashTable<T>::growTable() {
	vector<T> newTable;
	newTable.resize(GROW_FACTOR * table.size(), NIL);
	
	for (unsigned int i = 0; i < table.size(); i++) {
		if (table[i] == NIL || table[i] == DEL)
			continue;
		int newHash = Hash(table[i], newTable.size());
		int newHash2 = Hash2(table[i], newTable.size());
		int stepsCount = 0;
		while (newTable[newHash] != NIL && stepsCount < newTable.size()) {
			newHash = (newHash + newHash2) % newTable.size();
			stepsCount++;
		}	
		newTable[newHash] = table[i];
	}
	
	
	table = newTable;
	
}


int main()
{
	string NIL = "NIL", DEL = "DEL";
	HashTable<string> table(NIL, DEL);
	char operation;
	string word;
	while (cin >> operation >> word) {
		if (operation == '+')
			cout << (table.Add(word) ? "OK" : "FAIL") << '\n';
		if (operation == '-')
			cout << (table.Delete(word) ? "OK" : "FAIL") << '\n';
		if (operation == '?')
			cout << (table.Has(word) ? "OK" : "FAIL") << '\n';
	}
    return 0;
}

