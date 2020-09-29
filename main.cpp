
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/****************************************************************
struct KeyValue

Object holds a key/value pair

*****************************************************************/
struct KeyValue : pair<int, string> {
	int key;
	string value;
	KeyValue(int n=0, string s="") {
		key = first = n;
		value = second = s;
	}
	void setKey(int k) {
		key = first = k;
	}
	void setValue(string v) {
		value = second = v;
	}
};


/****************************************************************
class Dictionary

Vector wrapper Uses vector interface to perform functionality 
of a dictionary

*****************************************************************/

class Dictionary {
private: 
	vector<KeyValue> dictionary;
	int dictSize;
public:
	Dictionary(int);
	vector<KeyValue> getDictionary();
	void setDictionary(vector<KeyValue>);
	void Push_Back(KeyValue);
	void Resize(int);
	int getSize();
	KeyValue& operator[](int key);
};

Dictionary::Dictionary(int n = 0) {
	Resize(n);
}

void Dictionary::Push_Back(KeyValue kv) {
	dictionary.push_back(kv);
	dictSize = dictionary.size();
}

void Dictionary::Resize(int n) {
	dictSize = n;
	dictionary.resize(dictSize);
}

int Dictionary::getSize() {
	dictSize = dictionary.size();
	return dictSize;
}

vector<KeyValue> Dictionary::getDictionary() {
	return dictionary;
}

void Dictionary::setDictionary(vector<KeyValue> kv) {
	dictionary = kv;
}

KeyValue& Dictionary::operator[](int key) {
	if (key > dictSize - 1) {
		dictSize = dictionary.size();
		throw "out of bounds";
	}
	return dictionary[key];
}
