#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "assignment8.h"

using namespace std;

Entry* get_entry(const string& line)
{
	Entry* e = new Entry; //allocate memory for the new entry object
	e->key = line.substr(2, 3); //set entry's key value to specified string in line of text
	e->description = line.substr(6, '\n'); //set entry's description to specified string in line of text
	return e;
}
string get_key(const string& line)
{
	return line.substr(2, 3); //return specified string in line of text
}

// key is in form of letter-letter-digit
// compute sum <-- ascii(pos1)+ascii(pos2)+ascii(pos3)
// compute sum%htable_size
int HT::hashing(const string& key) {
	return ((int)key[0] + (int)key[1] + (int)key[2]) % table_size;
}

int main(int argc, char** argv) {
	if (argc < 2) {
		cerr << "argument: file-name\n";
		return 1;
	}

	HT ht;
	ifstream infile(argv[1], ios::in);
	string line;
	infile >> line;
	while (!infile.eof()) {
		if (line[0] == 'A') {
			Entry* e = get_entry(line);
			ht.insert(*e);
			delete e;
		}
		else {
			string key = get_key(line);
			if (line[0] == 'D') {
				cout << "Removing " << key << "...\n";
				bool removed = ht.remove(key);
				if (removed)
					cout << key << " is removed successfully...\n\n";
				else
					cout << key << " does not exist, no key is removed...\n\n";
			}
			else if (line[0] == 'S') {
				int found = ht.search(key);
				if (found < 0)
					cout << key << " does not exist in the hash table ..." << endl << endl;
				else
					cout << key << " is found at table position " << found << endl << endl;
			}
			else if (line[0] == 'P') {
				cout << "\nDisplaying the table: " << endl;
				ht.print();
			}
			else
				cerr << "wrong input: " << line << endl;
		}
		infile >> line;

	}

	infile.close();
	return 0;
}

