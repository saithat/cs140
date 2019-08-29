#include <cstdio>
#include <iostream>

using namespace std;

/* Problem 2:
 *
 * push() should check for out of bounds and type of variable
 * pop() should check that index is decreasing evey time it decreases and making sure no keeps running pop even when stack is empty
 * top() should make sure it is removing from the end of the array
 * */

class stack
{
	public:
		stack();
		~stack();

		bool empty() const
		{
			return N == 0;
		}	
		int size() const
		{
			return N;
		}
		void push(const int &din);
		void pop();
		const int & top();

	private:
		int N, Nmax;
		int *arr;
};

stack::stack()
{
	N = 0;
	Nmax = 10;

	arr = new int[Nmax];
}
stack::~stack()
{
	delete [] arr;
}

void stack::push(const int &din)
{
	arr[N] = din;
	N++;
}
void stack::pop()
{
	arr[N] = 0;
	N--;
}
const int &stack::top()
{
	return arr[N-1];
}

