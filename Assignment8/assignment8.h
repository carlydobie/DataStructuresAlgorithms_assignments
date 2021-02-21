#ifndef ASSIGNMENT8_H
#define ASSIGNMENT8_H
#include <vector>
#include <string>
#include <iostream>
#include <iomanip>

const int DEFAULT_SIZE = 11; //as specified in assignment instructions

//each entry in the hash table vector:
struct Entry {
	std::string key;
	std::string description;

	Entry() { key = "---"; }
};

//hash table:
class HT {
private:
	std::vector<Entry>* hTable; //vector to hold entries in hash table
	int table_size; //size of the table
	int item_count; //number of items in the table
	int hashing(const std::string&); //hashing algorithm
public:
	HT(); //default constructor
	HT(int size); //constructor
	~HT(); //destructor
	bool insert(const Entry&); //inserts element into the hash table
	int search(const std::string&); //searches for an element in the hash table
	bool remove(const std::string&); //removes an element from the hash table
	void print(); //prints out the current hash table
};

using namespace std;

HT::HT() //default constructor
{
	table_size = DEFAULT_SIZE; //initialize table size
	item_count = 0; //initialize item count
	hTable = new vector<Entry>[table_size]; //create blank entries in the vector
	hTable->resize(table_size); //set the size of the table
}
HT::HT(int size)
{
	table_size = size; //initialize table size
	item_count = 0; //initialize item count
	hTable = new vector<Entry>[table_size]; //create blank entries in the vector
	hTable->resize(table_size); //set the size of the table
}
HT::~HT()
{
	delete[] hTable; //delete all objects in vector
}
bool HT::insert(const Entry& e)
{
	auto i = hTable->begin() + hashing(e.key); //point iterator to location e should be at according to hash
	if (i->key == "---") //if entry is empty
	{
		i->key = e.key; //set key at current index
		i->description = e.description; //set description at current index
		item_count++; //tally item count
		return true;
	}
	else //index location has already been filled
	{
		for (i++; i != hTable->end(); i++) //point iterator to one after location e should be at according to hash
		{
			if (i->key == "---") //if entry is empty
			{
				i->key = e.key; //set key at current index
				i->description = e.description; //set description at current index
				item_count++; //tally item count
				return true;
			}
		}
		for (i = hTable->begin(); i != hTable->begin() + hashing(e.key); i++) //point iterator to beginning and stop when reaching original index
		{
			if (i->key == "---") //if entry is empty
			{
				i->key = e.key; //set key at current index
				i->description = e.description; //set description at current index
				item_count++; //tally item count
				return true;
			}
		}
	}
	return false; //entry was not added to table
}
int HT::search(const string& s)
{
	auto i = hTable->begin() + hashing(s); //point iterator to where s should be according to hash
	if (s == i->key) //if s is equal to the key at the location
		return hashing(s); //return the location of s in the table
	else //if s is not found at it's location specified by it's hash
	{
		int distance = 0; //set distance from starting point to zero
		for (i++; i != hTable->end(); i++) //point iterator to one after s should be according to hash
		{
			distance++; //tally distance
			if (s == i->key) //if s is equal to the key at the current location
				return hashing(s) + distance; //return the location of s in the table
		}
		distance = 0; //set distance for new starting point to zero
		for (i = hTable->begin(); i != hTable->begin() + hashing(s); i++) //point iterator to beginning of table and stop when reaching original location
		{
			distance++; //tally distance
			if (s == i->key) //if s is equal to the key at the current location
				return distance; //return the location of s in the table
		}
	}
	return -1; //s was not found in the table
}
bool HT::remove(const string& s)
{
	if (search(s) > 0) //if s is in the table
	{
		auto i = hTable->begin() + search(s); //point iterator to the location of s in the table
		i->key = "---"; //set key to default
		i->description = " "; //overwrite description
		item_count--; //subtract one from the item count
		return true;
	}
	return false; //s was not removed from the table
}
void HT::print()
{
	cout << endl;
	cout << "----Hash Table-----" << endl;
	for (auto i = hTable->begin(); i != hTable->end(); i++)
	{
		if (i->key != "---") //if there is an entry at the current location
		{
			cout << setw(4) << search(i->key) << ": "; //print the location of the current key
			cout << setw(3) << i->key << " "; //print the key
			cout << i->description << endl; //print the description
		}
	}
	cout << "-------------------" << endl << endl;
}

#endif

