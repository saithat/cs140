#include <iostream>
#include <list>
using namespace std;

template <typename iT, typename T>
int ex_count(iT i1, iT i2, const T &tar)
{
	int count = 0;
	while(i1 != i2)
	{
		if(*i1 == tar)
		{
			count++;
		}
		i1++;
	}
	return count;
}
int main() 
{
	list<int> v;
	list<int>::iterator iv;
	int value;
	while (cin >> value)
		v.push_back(value);
	int target = *v.begin();
	int N = ex_count(v.begin(), v.end(), target);
	cout << "Found " << N << " instances of " << target << "\n";
}
