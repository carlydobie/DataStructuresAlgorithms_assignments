//NIU CSCI 340 Spring 2019
//Assignment 1 - Search Algorithms
//Carly Dobie
//January 30 2019

#include <algorithm>
#include <iostream> //for cout <<
#include <vector>
#include <iomanip> //for setw() function
using namespace std;

const int DATA_SIZE = 200;
const int DATA_RANGE = 200;
const int DATA_SEED = 9;
const int SEARCH_SEED = 17;
const int NO_ITEMS = 8;
const int ITEM_W = 4;

int linear_search(const vector<int>& inputVec, const int x, int& comparisons) 
{
	comparisons = 0; //initialize comparisons
	for (int i = 0; i < inputVec.size(); i++) //go through all integers in vector
	{
		comparisons++; //tally comparisons
		if (inputVec[i] == x) //if current integer matches the integer being searched for
		return i; //return index of integer
	}
	return -1; //if x was not found, return -1
}

int binary_search(const vector<int>& inputVec, const int x, int& comparisons) 
{
	int l = 0; //initialize left 
	int r = inputVec.size(); //initialize right
	comparisons = 0; //initialize comparisons
	
    while (l <= r)  //continues while the left value is less than or equal to the right
    { 
        int m = l + (r - l) / 2; //initialize middle value

        if (inputVec[m] == x) //if x is the middle value
        {
			comparisons++; //tally comparisons
            return m; //return middle value
		}
        else if (inputVec[m] < x) //if middle value is less than x
        { 
			comparisons++; //tally comparisons
            l = m + 1; //new l contains values up to one after m (narrows down list)
		}
        else if (inputVec[m] > x) //if middle value is more than x
        {
			comparisons++; //tally comparisons
            r = m - 1; //new r contains values up to one before m (narrows down list)
		}
    } 
    return -1; //if x was not found, return -1
}

void print_vec(const vector<int>& vec) //prints out values in vector
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

void average_comparisons(const vector<int>& inputVec, const vector<int>& searchVec, int (*search)(const vector<int>&, const int, int&)) 
{
    int i, comparison = 0, sum = 0, found = 0;
    int res = 0;
    for (i = 0; i < (int)searchVec.size(); i++) 
    {
        res = search(inputVec, searchVec[i], comparison);
        sum += comparison;
        if (res >= 0)
           found++;
    }
    cout << found << " numbers are found. The average number of comparisons in each search: " << (double)sum/(double)searchVec.size() << endl << endl;
}

int random_number() 
{
    return rand()%DATA_RANGE + 1;
}

int main () 
{

    // -------- create unique random numbers ------------------//
    vector<int> inputVec(DATA_SIZE);
    srand(DATA_SEED);
    generate(inputVec.begin(), inputVec.end(), random_number); //generate vector of random ints
    sort(inputVec.begin(), inputVec.end()); //sort vector
    vector<int>::iterator it = unique(inputVec.begin(), inputVec.end());
    inputVec.resize(it - inputVec.begin());
    random_shuffle(inputVec.begin(), inputVec.end()); //shuffle vector

    cout << "------ Data source: " << inputVec.size() << " unique random numbers ------" << endl; 
    print_vec(inputVec);
    cout << endl;

    // -------- create random numbers to be searched ---------//
    vector<int> searchVec(DATA_SIZE/2);
    srand(SEARCH_SEED);
    generate(searchVec.begin(), searchVec.end(), random_number); //generate vector of random ints

    cout << "------ " << searchVec.size() << " random numbers to be searched: ------" << endl;
    print_vec(searchVec);
    cout << endl;

    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    sort(inputVec.begin(), inputVec.end());
    cout << "------- numbers in data source are now sorted ---------" << endl << endl;
    cout << "Linear search: ";
    average_comparisons(inputVec, searchVec, linear_search);
    cout << "Binary search: ";
    average_comparisons(inputVec, searchVec, binary_search);

    return 0;
}


