
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
class Parser

Parses text based on user defined delimiter and returns parsed
content through a vector

*****************************************************************/
class Parser {
private:
	string text;
	const char* delimiter;
public:
	vector<int> parse(string t, const char* d);
	const char* getDelimiter();
	void setDelimiter(const char*);
};

vector<int> Parser::parse(string t, const char* d) {
	vector<int> vlist;
	text = t;
	delimiter = d;
	string temp;
	// find delimiter in text
	int start = 0;
	int index = text.find(*delimiter);
	while (index != string::npos) {
		// put value between delimiter into temp
		temp.assign(text, start, index - start);
		// push number into vector
		vlist.push_back(stoi(temp));
		// find next delimiter
		start = index + 1;
		index = text.find(*delimiter, start);
	}
	return vlist;
}

const char* Parser::getDelimiter() {
	return delimiter;
}

void Parser::setDelimiter(const char* d) {
	delimiter = d;
}



/****************************************************************
class File

File class is an object with capability of performing file 
operations such as read from and write to files. 

*****************************************************************/
template <typename T>
class File {
private:
	string directory;
public:
	File();
	File(string);
	string getDirectory();
	void setDirectory(string);
	void writeFile();
	void readFile(vector<int>&, const char*);
};

template <class T>
File<T>::File() {
	directory = "Encrypted.txt";
}

template <class T>
File<T>::File(string s) {
	directory = s;
}

template <class T>
string File<T>::getDirectory() {
	return directory;
}

template <class T>
void File<T>::setDirectory(string s) {
	directory = s;
}

template <class T>
void File<T>::writeFile() {
	ofstream myFile();
	myFile.open(directory);
	// open file
	if (myFile.is_open()) {
		string text;
		getline(cin, text);
		//myFile << text;
	}
	else {
		throw "No File to write to";
	}
	myFile.close();
}

template <class T>
void File<T>::readFile(vector<int> &list, const char* delimiter) {
	
	ifstream myFile;
	myFile.open(directory);
	
	// open file
	if (!myFile.is_open()) {
		cout << "file not open" << endl;
		system("pause");
	}

	while(!myFile.eof()) {
		// get text from file
		string buffer = "";
		getline(myFile, buffer);
		// parse text into vector
		Parser decode;
		vector<int> newList = decode.parse(buffer, delimiter);
		// place vector into list passed into function
		list.insert(list.end(), newList.begin(), newList.end());
		// clear newList
		newList.clear();
	}
	myFile.close();
}



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
