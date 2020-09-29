
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


/****************************************************************
class Decryption

Decryption class decrypts content seperated by vector indexes

*****************************************************************/
class Decryption {
private:
	int size;
public:
	Decryption(int);
	string Decrypt(vector<int>::iterator, vector<int>::iterator);
};

Decryption::Decryption(int s = 256) {
	size = s;
}

string Decryption::Decrypt(vector<int>::iterator begin, vector<int>::iterator end) {

	Dictionary dictionary(size);
	// set vector indexes to ascii code
	for (int i = 0; i < size; i++) {
		dictionary[i].setKey(i);
		dictionary[i].setValue(string(1, i));
	}
	int key;
	string word(1, *begin++);
	string result = word;
	string entry;
	
	
	while (begin != end) {
		key = *begin;
		size = dictionary.getSize();
		// find key and return value
		if (key >= 0 && key < size)
			entry = dictionary[key].value;
		else if (key == size)
			entry = word + word[0];
		else
			throw "Invalid Key";
		
		// add decoded entry to result string
		result += entry;
		// push entry into dictionary 
		KeyValue kv(dictionary.getSize(), word + entry[0]);
		dictionary.Push_Back(kv);
		word = entry;

		begin++;
	}
	return result;
}
