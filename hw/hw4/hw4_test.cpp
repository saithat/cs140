#include <cstdio>
#include <iostream>
#include <array>

using namespace std;

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

int main(int argc, char *argv[]){  stack v;  int value;  cout << "enter values:\n";  while (cin >> value) {    v.push(value);    cout << value << "\n";  }  cout << "--- LIFO\n";  while (!v.empty()) {    value = v.top();    v.pop();    cout << value << "\n";  }}
