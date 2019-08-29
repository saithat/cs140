#include <iostream>
#include <cstdio>
#include <ctype.h>
#include <cmath>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <vector>
//#include <clibstd>

using namespace std;

class isprime {
  public:
    isprime() {primes.push_back(2); }
    bool operator()(int);
	list<int>::iterator iter;

  private:
	list<int> primes;
	bool prime_func(int);
	void listAddr(int);
};

bool isprime::operator()(int num)
{
	listAddr(num);

	return binary_search(primes.begin(), primes.end(), num);
}
bool isprime::prime_func(int num)
{
	if(num <= 1)
		return false;
	int root = (int)((pow(num,.5)));
	for(int i=2; i <=root; i++)
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
	for(int i = primes.back(); i < n; i++)
	{
		if(prime_func(i))
			primes.push_back(i);
	}
	for(int j = n;;j++)
	{
		if(prime_func(j))
		{
			primes.push_back(j);
			return;
		}
	}
}

int random_number()
{
	return rand()%140 + 1;
}

int main(int argc, char *argv[])
{
	int N = 123;

	if(argc == 2)
	{
		N = atoi(argv[1]);
	}


	srand(N);

	vector<int> list (N); 
	vector<bool> p (N);

	isprime op;

	generate(list.begin(),list.end(), random_number);
	transform(list.begin(), list.end(), p.begin(), isprime());
	int c = count(p.begin(),p.end(), true);

	cout << "Sequence contains " << c << " prime numbers." << endl;
}
