#ifndef ASSIGNMENT4_H
#define ASSIGNMENT4_H
#include <stack>

class Queue {
    private:
        std::stack<int> s1, s2;
    public:
        bool empty() const;
        int size() const;
        int front();
        int back();
        void push(const int& val);
        void pop();
};

bool Queue::empty() const //checks if s1 and s2 are empty or not
{
	if (s1.empty() && s2.empty()) //if s1 and s2 are empty
		return true;
	else //if there's at least one element in one of the stacks
		return false;
}
int Queue::size() const //returns the size of s1 and s2 combined
{
	return s1.size() + s2.size();
}
int Queue::front() //returns the oldest element
{
	if (s2.empty() && !s1.empty()) //if s2 is empty and s1 is not
	{
		while (!s1.empty()) //loop continues as long as s1 is not empty
		{
			s2.push(s1.top()); //push s1's top element onto s2
			s1.pop(); //pop top element from s1
		}
	}
	return s2.top(); //returns reference to s2's top element
}
int Queue::back() //returns newest element
{	
	if (s1.empty() && !s2.empty()) //if s1 is empty and s2 is not
	{
		while (!s2.empty()) //loop continues as long as s2 is not empty
		{
			s1.push(s2.top()); //push s2's top element onto s1
			s2.pop(); //pop top element from s2
		}
	}
	return s1.top(); //returns reference to s1's top element
}
void Queue::push(const int& val) //adds element to s1
{
	s1.push(val); //push val onto s1 stack
}
void Queue::pop() //removes the oldest element
{
	front(); //perform function to get top element in position
	s2.pop(); //remove the top element
}

#endif
