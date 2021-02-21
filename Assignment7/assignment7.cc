#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>

using namespace std;

const int HEAP_SIZE = 50;

//function declarations:
void build_heap(vector<int>& v, int heap_size, bool (*compar)(int, int));
void heapify(vector<int>& v, int heap_size, int r, bool (*compar)(int, int));
bool less_than(int el, int e2);
bool greater_than(int el, int e2);
bool heap_sort(vector<int>& v, int heap_size, bool (*compar)(int, int));
int extract_heap(vector<int>& v, int& heap_size, bool (*compar)(int, int));
void print_vector(vector<int>& v, int pos, int size);

int main(int argc, char** argv) {
    // ------- creating input vector --------------
    vector<int> v;
    v.push_back(-1000000);    // first element is fake
    for (int i=1; i<=HEAP_SIZE; i++)
        v.push_back( i );
    random_shuffle( v.begin()+1, v.begin()+HEAP_SIZE+1 );

    cout << "\nCurrent input numbers: " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing min heap ------------------
    cout << "\nBuilding a min heap..." << endl;
    build_heap(v, HEAP_SIZE, less_than);
    cout << "Min heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, less_than);
    cout << "Heap sort result (in ascending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    // ------- testing max heap ------------------
    cout << "\nBuilding a max heap..." << endl;
    build_heap(v, HEAP_SIZE, greater_than);
    cout << "Max heap: " << endl;
    print_vector( v, 1, HEAP_SIZE );
    heap_sort( v, HEAP_SIZE, greater_than);
    cout << "Heap sort result (in descending order): " << endl;
    print_vector( v, 1, HEAP_SIZE );

    return 0;
}

void build_heap(vector<int>& v, int heap_size, bool (*compar)(int, int)) //constructs a heap with heap_size elements in the vector v
{
	heapify(v, heap_size, 1, compar); //create heap from values in v starting at index 1
}
void heapify(vector<int>& v, int heap_size, int r, bool (*compar)(int, int)) //"heapifies" a tree at the root position r, assuming r's two sub-trees are already heaps
{
	int leftchild = (2*r); //left child's position in relation to curent
	int rightchild = (2*r) + 1; //right child's position in relation to current

	if (v[leftchild] != 0 && v[rightchild] != 0) //both children must exist
	{
		if (leftchild < heap_size && rightchild < heap_size) //values of the children must be less than 51
		{
			if (compar(v[leftchild], v[r])) //compare left child to current
			{
				swap(v[r], v[leftchild]); //swap current with current's left child
				heapify(v, heap_size, leftchild, compar); //heapify left sub-tree
			}
			if (compar(v[rightchild], v[r])) //compare right child to current
			{
				swap(v[r], v[rightchild]); //swap current with current's right child
				heapify(v, heap_size, rightchild, compar); //heapify right sub-tree
			}
			if (compar(v[r], v[1])) //compare current to root
			{
				swap(v[1], v[r]); //swap root with current
			}
			heapify(v, heap_size, r + 1, compar); //heapify next value in vector
		}
	}
}
bool less_than(int el, int e2) //compares two integers and returns ture if el is less than e2
{
	if (el < e2) //if el is less than e2
		return true;
	else
		return false;
}
bool greater_than(int el, int e2) //compares two integers and returns true if el is greater than e2
{
	if (el > e2) //if el is greater than e2
		return true;
	else
		return false;
}
bool heap_sort(vector<int>& v, int heap_size, bool (*compar)(int, int))
{
	build_heap(v, heap_size, compar); //rebuild heap to mix up values

	for (int i = heap_size; i > 1; i--)
	{
		extract_heap(v, i, compar); //moves extreme value to end of array and heapifies the array without that integer to find next extreme
	}
	reverse(v.begin() + 1, v.end()); //reverse the order of the array

	return true;
}
int extract_heap(vector<int>& v, int& heap_size, bool (*compar)(int, int)) //extracts the root of the heap recorded in v, fills the root with the last element of the current heap, updates heap_size, "heapifies" at the root, and returns the old root value.
{
	swap(v[1], v[heap_size]); //swap first and last
	heapify(v, heap_size, 1, compar); //heapify to find new heap top

	return v[1]; //return top of heap
}
void print_vector(vector<int>& v, int pos, int size) //displays size number of elements contained in vector v starting at position pos
{
	int rcount = 0; //row count

	for (int i = pos; i < size + 1; i++)
	{
		cout << setw(5) << v.at(i); //prints integer at i in 5 spaces
		rcount++; //tally rowcount
        if (rcount == 8) //when rowcount reaches 8
        {
            cout << endl; //line break
            rcount = 0; //reset row count
        }
    }
    cout << endl;
}
