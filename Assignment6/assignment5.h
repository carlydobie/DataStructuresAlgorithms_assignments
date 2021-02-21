#ifndef ASSIGNMENT5
#define ASSIGNMENT5
#include <cstddef>
#include <iostream>
#include <algorithm>

//node class:
class Node {
public:
	Node(); //default constructor
	Node(const int& x); //constructor
	int data; //holds integer value
	Node* left; //pointer to left child
	Node* right; //pointer to right child
	friend class binTree;
	friend class BST;
};
Node::Node() //default constructor
{
	data = 0;
	left = nullptr;
	right = nullptr;
}
Node::Node(const int&x) //constructor
{
	data = x; //set data to x
	left = nullptr;
	right = nullptr;
}

//binary tree class:
class binTree {
public:
	binTree(); //default constructor
	virtual void insert(int x); //calls private insert function
	int height() const; //calls private height function
	unsigned size() const;  //calls private size function
	void inorder(void(*)(int)); //calls private inorder function
	void preorder(void(*)(int)); //calls private preorder function
	void postorder(void(*)(int));  //calls private postorder function

protected:
	Node * root; //root node of the tree

private:
	void insert(Node*& r, int x); //inserts a node into the tree
	int height(Node* r) const; //calculates the height of each sub tree
	unsigned size(Node* r) const; //calculates the total size of the tree
	void inorder(Node*, void(*)(int)); //traverses the tree in inorder LNR
	void preorder(Node*, void(*)(int)); //traverses the tree in preorder NLR
	void postorder(Node*, void(*)(int)); //traverses the tree in postorder LRN
};

//public member functions:
binTree::binTree() //constructor
{
	root = nullptr; //initialize root
}
void binTree::insert(int x)
{
	insert(root, x);
}
int binTree::height() const
{
	return height(root);
}
unsigned binTree::size() const
{
	return size(root);
}
void binTree::inorder(void(*p)(int))
{
	inorder(root, p);
}
void binTree::preorder(void(*p)(int))
{
	preorder(root, p);
}
void binTree::postorder(void(*p)(int))
{
	postorder(root, p);
}
//private member functions:
void binTree::insert(Node*& r, int x) //inserts a node into the shortest sub tree
{
	if (!r) //if node doesn't exist
		r = new Node(x); //create the node
	else
	{
		if (height(r->left) <= height(r->right)) //if left subtree is less than or equal to the right sub tree
			insert(r->left, x); //call insert on left node
		else if (height(r->left) > height(r->right)) //if left subtree is greater than the right sub tree
			insert(r->right, x); //call insert on right node
	}
}
int binTree::height(Node* r) const //returns the height of the tree
{
	if (!r) //if node doesn't exist
		return -1; //subtract the 1 that was added with the last recursive call
	else
		return (std::max(height(r->left), height(r->right)) + 1); //return the max calculated height + 1
}
unsigned binTree::size(Node* r) const //returns the size of the tree
{
	if (!r) //if node doesn't exist
		return 0;
	else
		return (size(r->left) + 1 + size(r->right)); //recursively call size on left and right subtree, adding 1 each time
}
void binTree::inorder(Node* r, void(*p)(int)) //traverses tree LNR
{
	if (!r) //if node doesn't exist
		return;
	else
	{
		inorder(r->left, p); //move to left
		p(r->data); //display current node's data
		inorder(r->right, p); //move to right
	}
}
void binTree::preorder(Node* r, void(*p)(int)) //traverses tree NLR
{
	if (!r) //if node doesn't exist
		return;
	else
	{
		p(r->data); //display current node's data
		preorder(r->left, p); //move to left
		preorder(r->right, p); //move to right
	}
}
void binTree::postorder(Node* r, void(*p)(int)) //traverses tree LRN
{
	if (!r) //if node doesn't exist
		return;
	else
	{
		postorder(r->left, p); //move to left
		postorder(r->right, p); //move to right
		p(r->data); //display current node's data
	}
}
#endif

