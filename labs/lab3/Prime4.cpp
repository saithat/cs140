#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <list>
#include <algorithm>
#include <vector>
#include <iomanip>
using namespace std;

class isprime {
  public:
    isprime() { }
    bool operator()(int);
	list<int>::iterator iter;
  private:
	list<int>primes;
	bool prime_func(int num);
	void listAddr(int);
};

bool isprime::operator()(int num)
{
	if((num > primes.back()))
	{
		listAddr(num);
	}
	return binary_search(primes.begin(), primes.end(), num);
}
bool isprime::prime_func(int num)
{
	if(num <= 1)
		return false;

	int root = (int)((pow(num, .5)));
	for(int i=2; i<=root; i++)
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

void extract_prime(vector<int> num_list, vector<bool> p, vector<int> &test)
{
	vector<bool>::iterator i;
	int j = 0;
	for(i=p.begin(); i!= p.end(); i++)
	{
		if(*i == true)
		{
			test.push_back(num_list[j]);
		}
		j++;
	}
}

void print(vector<int> list)
{
	int counter = 1;
	for(vector<int>::iterator i = list.begin(); i!= list.end(); i++)
	{
		cout << " " << setw(3) << *i;
		cout << " ";
		if(counter == 8)
		{
			cout << endl;
			counter = 0;
		}
		counter++;
	}
	cout << endl;
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

	generate(list.begin(), list.end(), random_number);
	transform(list.begin(), list.end(), p.begin(), isprime());

	int c = count(p.begin(), p.end(), true);
	
	cout << "Sequence contains " << c << " prime numbers." << endl;


	vector<int> prime_num;
	extract_prime(list, p, prime_num);

	cout << "All numbers in order appearance: " << endl;

	print(prime_num);

	sort(prime_num.begin(), prime_num.end());

	vector<int>::iterator it;

	it = unique(prime_num.begin(), prime_num.end());

	prime_num.erase(it, prime_num.end());

	cout << "Unique values in numerical order: " << endl;

	print(prime_num);

}
