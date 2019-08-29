#include <iostream>
#include <list>
using namespace std;

template <typename T>
class ex_eq
{
	public:
		ex_eq(const T &n_target) { target = n_target; }
		bool operator() (const T &v) const { return v == target; }
	private:
		T target;
};

template <typename iT, typename F>
int ex_count(iT i1, iT i2, F target)
{
	int count = 0;
	while(i1 != i2)
	{
		if(target(*i1))
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
	int N = ex_count(v.begin(), v.end(), ex_eq<int>(target));
	cout << "Found " << N << " instances of " << target << "\n";
}
