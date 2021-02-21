#ifndef ASSIGNMENT6
#define ASSIGNMENT6
#include "assignment5.h" //contains binTree class and node class
using namespace std;

//binary search tree class:
class BST : public binTree { //child class of binTree class
public:
	BST() : binTree() {} //default constructor
	virtual void insert(int x); //calls BST private insert member function
	bool search(int x); //calls private search member function
	bool remove(int x); //calls private remove member function
	int sumLeaves(); //calls private sumLeaves member function
private:
	void insert(Node*& r, int x);
	bool search(Node*& r, int x);
	bool remove(Node*& r, int x);
	int sumLeaves(Node*& r);
	Node* findMin(Node*& r);
};
//public member functions:
void BST::insert(int x)
{
	insert(root, x);
}
bool BST::search(int x)
{
	return search(root, x);
}
bool BST::remove(int x)
{
	return remove(root, x);
}
int BST::sumLeaves()
{
	return sumLeaves(root);
}
//private member functions
void BST::insert(Node*& r, int x) //inserts node to left if less than current, right if greater than current
{
	if (!r) //if node doesn't exist
		r = new Node(x); //create new node with data x
	else
	{
		if (x < r->data) //if x is less than the current node's data
			insert(r->left, x); //try inserting node into left subtree
		else if (x > r->data) //if x is greater than the current node's data
			insert(r->right, x); //try inserting node into right subtree
	}
}
bool BST::search(Node*& r, int x) //search's for node with data matching x
{
	 if (!r) //if node doesn't exist
		return false;
	 if (x == r->data) //if node is found
		 return true;
	 else if (x < r->data) //if x is less than current node's data
		 search(r->left, x); //search left subtree
	 else if (x > r->data) //if x is greater than current node's data
		 search(r->right, x); //search right subtree
}
bool BST::remove(Node*& r, int x) //removes node with data matching x
{
	if (!r) //if node doesn't exist
		return false;
	if (x < r->data) //if x is less than current node's data
        remove(r->left, x); //search for x in left subtree
    else if (x > r->data) //if x is greater than current node's data
        remove(r->right, x); //search for x in right subtree
    else if (x == r->data) //if node to delete is found
    {
        if (!r->left && !r->right) //if node to delete is a leaf
        {
            delete r; //delete node
            r = nullptr;
            return true;
        }
        else //if node to delete has children
        {
            if (r->left && !r->right) //if node only has a left child
            {
                Node* tmp = r;
                r = r->left;
                delete tmp;
                r = nullptr;
                return true;
            }
            else if (r->right && !r->left) //if node only has a right child
            {
                Node* tmp = r;
                r = r->right;
                delete tmp;
                r = nullptr;
                return true;
            }
            else if (r->left && r->right) //if node has two children
            {
				if (!r)
					return false;
				else
				{
					Node* tmp = findMin(r->right);
					r->data = tmp->data;
					//delete tmp;
					tmp = nullptr;
					return true;
				}
            }
        }
    }
}
int BST::sumLeaves(Node*& r) //sums the data of all leaf nodes
{
	int sum = 0; //initialize sum

	if (!r) //if node doesn't exist
		return 0;
	else
	{
		if (!r->left && !r->right) //if node doesn't have children (is a leaf)
			sum += r->data; //sum it's data
		else
			sum += sumLeaves(r->left); //sum left subtree leaves

		sum += sumLeaves(r->right); //sum right subtree leaves
	}
	return sum;
}
Node* BST::findMin(Node*& r)
{
	if (r->left) //if left child exists
		if (r->left->left)
			findMin(r->left); //move to left child's left child
	else
		return r;
}
#endif

