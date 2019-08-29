#include <iostream>
#include <string>
using namespace std;

template <typename T>
class stats 
{
	public:
		stats();
		T sum;
		void push(T);
		void print();
		int N;
};

template<typename T>
stats<T>::stats()
{
	sum = T();
	N = 0;
}

template<typename T>
void stats<T>::push(T num)
{
	N++;
	sum += num;
}
template<typename T>
void stats<T>::print()
{
	cout << "N   = " << N << "\nsum = " << sum << endl;
}

int main()
{
	string num;
	stats<string>user;
	cin >> num;
	user.sum = num;
	user.N = 1;

	while(cin >> num)
	{
		user.push(num);
	}

	user.print();

	return 0;
}
