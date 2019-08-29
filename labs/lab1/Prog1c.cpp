#include <iostream>
using namespace std;

class stats 
{
	public:
		void push(int num);
		void print();
		int counter;
		int min;
		int max;
		int sum;
};

void stats::push(int num)
{
	counter++;
	sum += num;
	if(num < min)
	{
		min = num;
	}
	if(num > max)
	{
		max = num;
	}
}

void stats::print()
{
	cout << "N   = " << counter << "\nsum = " << sum << "\nmin = " << min << "\nmax = " << max << "\n";
}

int main()
{
	stats user;
	int num = 0;
	cin >> num;
	user.sum = num;
	user.min = num;
	user.max = num;
	user.counter = 1;

	while(cin >> num)
	{
		user.push(num);
	}

	user.print();

	return 0;
}
