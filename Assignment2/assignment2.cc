//NIU CSCI 340 Spring 2019
//Assignment 2 - STL Algorithms
//Carly Dobie
//February 6 2019

#include <algorithm>
#include <iostream> //for cout <<
#include <vector> //for vector funcitons
#include <iomanip> //for setw() function
#include <cstdlib> //for srand() and rand()
using namespace std;

const int DATA_SIZE = 100; //size of data vector
const int SEARCH_SIZE = 50; //size of vector containing elements to be searched for 
const int DATA_SEED = 11;
const int SEARCH_SEED = 7;
const int NO_ITEMS = 10; //number of items output to screen per line 
const int ITEM_W = 6; //for line output width

void genRndNums(vector<int>& v, int seed) 
{
	srand(seed); //initialize random numbers with given seed
	
	for (int i = 0; i < v.size(); i++) //cycle through elements in vector
	{
		v[i] = rand() % 100 + 1; //set current element in vector to random number
	}
}

bool linearSearch(const vector<int>& inputVec, int x) 
{
	if (find(inputVec.begin(), inputVec.end(), x) != inputVec.end()) //linear search for x in inputVec
		return true; //returns true if position is returned
	else 
		return false; //returns false if position of vector's end is returned
}

bool binarySearch(const vector<int>& inputVec, int x) 
{
	if (binary_search(inputVec.begin(), inputVec.end(), x)) //binary search for x in inputVec
		return true; //if x is found, returns true
	else
		return false; //if false (not found), returns false
}

int search(const vector<int>& inputVec, const vector<int>& searchVec,
            bool (*p)(const vector<int>&, int))
{
	int totalSucCnt = 0; //initialize total success count
	
	for (auto it = searchVec.begin(); it != searchVec.end(); it++) //iterate through search vector
	{
		if (p(inputVec, searchVec[*it])) //run specified search function on searchVec element in inputVec		
			totalSucCnt++; //if returns true, tally counter
	}
	
	return totalSucCnt; //return number of successful matches
}

void sortVector(vector<int>& inputVec) 
{
	sort(inputVec.begin(), inputVec.end()); //sorts vector
}

void printStat(int totalSucCnt, int vec_size) //prints out number of successful comparisons
{
	cout << "Total number of successful comparisons: " << totalSucCnt;
}

void print_vec(const vector<int>& vec)
{
	int counter = 0; //initialize counter for number of values output per line
	
	for (int i = 0; i < vec.size(); i++) 
	{
		if (counter == NO_ITEMS) //if NO_ITEMS has been printed to screen
		{
			cout << endl; //break line
			counter = 0; //reset counter
		}
		else //NO_ITEMS per line has not been reached
		{
			cout << setw(ITEM_W) << left << vec[i]; //set width of output to ITEM_W, output value
			counter++; //tally counter				//output characters starting at the left
		}
	}
}

int main() 
{
    vector<int> inputVec(DATA_SIZE);
    vector<int> searchVec(SEARCH_SIZE);
    genRndNums(inputVec, DATA_SEED);
    genRndNums(searchVec, SEARCH_SEED);

    cout << "----- Data source: " << inputVec.size() << " randomly generated numbers ------" << endl;
    print_vec(inputVec);
    cout << endl;
    cout << "----- " << searchVec.size() << " random numbers to be searched -------" << endl;
    print_vec(searchVec);

    cout << "\nConducting linear search on unsorted data source ..." << endl;
    int linear_search_count = search(inputVec, searchVec, linearSearch);
    printStat (linear_search_count, SEARCH_SIZE);

    cout << "\nConducting binary search on unsorted data source ..." << endl;
    int binary_search_count = search(inputVec, searchVec, binarySearch);
    printStat (binary_search_count, SEARCH_SIZE);

    sortVector(inputVec);

    cout << "\nConducting linear search on sorted data source ..." << endl;
    linear_search_count = search(inputVec, searchVec, linearSearch);
    printStat (linear_search_count, SEARCH_SIZE);

    cout << "\nConducting binary search on sorted data source ..." << endl;
    binary_search_count = search(inputVec, searchVec, binarySearch);
    printStat (binary_search_count, SEARCH_SIZE);

    return 0;
}

