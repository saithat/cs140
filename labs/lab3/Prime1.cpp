#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

bool isprime(int number) 
{
	if(number <= 1)
		return false;

	int root = (int)((pow(number, 0.5)));
	for(int i = 2; i <= root; i++)
	{
		if((number % i) == 0)
		{
			return false;
		}
	}
	return true;
};

int main()
{
	int number;

	while (cin >> number) {
	  if (isprime(number))
	    cout << number << " is prime!" << endl;
	}
}
