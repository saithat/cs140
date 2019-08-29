#include <iostream>
using namespace std;

int main()
{
	int counter = 0;
	int min;
	int max;
	int num = 0;
	int sum = 0;

	cin >> num;
	counter++;
	min = num;
	sum = num;
	max = num;
	while(cin >> num)
	{
		counter++;
		if(num > max)
		{
			max = num;
		}
		if(num < min)
		{
			min = num;
		}

		sum += num;
	}

	cout << "N   = " << counter << "\nsum = " << sum << "\nmin = " << min << "\nmax = " << max << "\n";

}
