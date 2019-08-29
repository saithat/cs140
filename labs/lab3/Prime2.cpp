#include <iostream>
#include <cstdio>
#include <cmath>
#include <list>
#include <algorithm>

using namespace std;

class isprime {
  public:
    isprime() {
		primes.push_back(2);
	}
    bool operator()(int);
	list<int>::iterator iter;

  private:
	list<int> primes;
	bool prime_func(int);
	void listAddr(int);
};

bool isprime::operator()(int number)
{
	listAddr(number);
    for(iter = primes.begin(); iter != primes.end(); iter++)
	{
		if(*iter == number)
		{
			return true;
		}
	}
	return false;
}

bool isprime::prime_func(int num)
{
	if(num <= 1)
		return false;

	int root = (int)((pow(num, 0.5)));
	for(int i=2; i<=root;i++)
	{
		if((num % i) == 0)
		{
			return false;
		}
	}
	return true;
}

void isprime::listAddr(int n)
{
	int i = ++n;
	while(!prime_func(i))
	{
		++i;
	}

	int curPrime = primes.back();

	if(i > curPrime)
	{
		for(int j = curPrime; j < i; j++)
		{
			if(prime_func(j))
			{
				primes.push_back(j);
			}
		}
	}
}

int main()
{
	isprime pcheck;
	int number;

	while ( cin >> number ) {
	  if (pcheck(number))
	    cout << number << " is Prime!" << endl;
	}
}
