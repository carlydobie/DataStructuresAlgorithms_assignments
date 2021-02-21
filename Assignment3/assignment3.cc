//NIU CSCI 340 Spring 2019
//Assignment 3 - Sieve of Eratosthenes
//Carly Dobie
//February 15 2019

#include <iostream>
#include <set>
#include <iomanip>
#include <cctype>

using namespace std;

const int NO_ITEMS = 6; //number of items output to screen per line 
const int ITEM_W = 4; //for line output width

void sieve(set<int>& s, const int lower, const int upper) //removes non-prime numbers
{
	
	for(auto it = s.begin(); it != s.end(); it++) //iterate through set
	{
		for(int m = 2; m < upper; m++) //initialize first multiple to 2
		{
			for(int n = 2; m * n < upper; n++) //initialize second multiple to 2
			{
				if(m*n == *it) //if product is in the set
				{
					it++; //move iterator forward
					s.erase(m*n); //erase non-prime integer
				}
			}
		}
	}
}

void print_primes(const set<int>& s, const int lower, const int upper) //prints out what's left of set
{
	cout << "The prime numbers between " << lower << " and " << upper << " are: " << endl;
	
	int counter = 0;
	
	for(auto it = s.begin(); it != s.end(); it++) //iterate through set
	{
			if (counter == NO_ITEMS) //if NO_ITEMS has been printed to screen
		{
			cout << endl; //break line
			counter = 0; //reset counter
		}
		else //NO_ITEMS per line has not been reached
		{
			cout << setw(ITEM_W) << left << *it << " "; //print out current integer 
			counter++; //tally counter				
		}
		
	}
	cout << endl;
}

void run_game(set<int>& s) 
{
	int u; //upper bound
	int l; //lower bound
	bool redo = false; //variable for ensuring user inputs correct bounds
	
	do
	{
		cout << "Enter in the highest value in range: ";
		cin >> u;
		cout << "Enter in the lowest value in range: ";
		cin >> l;
		
		if (l > u) //if lower bound is greater than upper bound
		{
			cout << "Your low value is greater than your high value! Try again." << endl; //tell user
			redo = true; 
		}
		else
		{
			redo = false; //exits do-while loop
		}
	}while(redo == true); //user prompted to enter bounds again if l > u
	
	for(int i = l; i <= u; i++) //starting at l, iterate through integers until reaching u
	{
		s.insert(i); //add integers into set
	}
	
	int counter = 0;
	
	cout << "The numbers in your range are: " << endl; //repeat numbers in range back to user
	for(auto it = s.begin(); it != s.end(); it++) //iterate through set
	{
			if (counter == NO_ITEMS) //if NO_ITEMS has been printed to screen
		{
			cout << endl; //break line
			counter = 0; //reset counter
		}
		else //NO_ITEMS per line has not been reached
		{
			cout << setw(ITEM_W) << left << *it << " "; //print out current integer 
			counter++; //tally counter				
		}
		
	}
	
	cout << endl;
	
	sieve(s, l, u); //remove non-prime numbers
	print_primes(s, l, u); //print out the prime numbers remaining in set
}

int main() 
{
	char again;
	
	do 
	{
		set<int> s;
    
		run_game(s); //prompts user for upper and lower bounds, creates set, then removes non-prime numbers from set
		
		cout << "Would you like to play again? (Y/N): ";
		cin >> again;
	}while(toupper(again) == 'Y');
    return 0;
}

