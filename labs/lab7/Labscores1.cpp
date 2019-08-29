#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <iomanip>
using namespace std;
class labscores_t
{
	public:
		labscores_t();
		labscores_t(const int);
		void add_data(const int);
		void set_stats();
		void print_labscores();
	private:
		vector<int> scores;
		int median;
		float mean;

};
labscores_t::labscores_t()
{

}
labscores_t::labscores_t(const int val)
{
	scores.push_back(val);
}
void labscores_t::add_data(const int sc)
{
	scores.push_back(sc);
}
void labscores_t::print_labscores()
{
	set_stats();
	for(vector<int>::iterator it = scores.begin(); it != scores.end(); it++)
	{
		cout << setw(2) << setfill(' ') << *it << " ";
	}
	cout << ":" << setw(3) << median << " " <<setw(3) << fixed << setprecision(1) << mean;
}
void labscores_t::set_stats()
{
	sort(scores.begin(), scores.end());  //sorts from least to greatest
	float sum = 0.0;
	sum = accumulate(scores.begin(), scores.end(), sum);
	mean = sum/scores.size();
	median = scores.at((scores.size()-1)/2);
}
class name_t
{
	public:
		name_t();
		name_t(string, string);
		bool operator<(const name_t &) const;
		void print_name(int) const;
	private:
		string firstname;
		string lastname;
};
name_t::name_t()
{
}
name_t::name_t(string first, string last)
{
	firstname = first;
	lastname = last;
}
bool name_t::operator<(const name_t &rhs) const
{
	if(lastname.compare(rhs.lastname) < 0)
	{
		return true;
	}
	if(lastname.compare(rhs.lastname) == 0)
	{
		if(firstname.compare(rhs.firstname) < 0)
		{
			return true;
		}
	}
	return false;

}
void name_t::print_name(int max) const
{
	cout << lastname << ", " << firstname << " " << setfill('.') << setw(max+3-lastname.length()-firstname.length()); 
}
int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		cerr << "usage: labscores -byname|byrank|top10 datafile.txt" << endl;
		return -1;
	}
	if(!(string(argv[1]) == "-byname"))
	{
		cerr << "usage: labscores -byname|byrank|top10 datafile.txt" << endl;
		return -2;
	}

	ifstream fin(argv[2]);

	string firstname, lastname, line;
	int score, max_length;
	max_length = 0;

	map<name_t,labscores_t> score_map;

	while(getline(fin, line))
	{
		istringstream ss(line);
		ss >> firstname;
		ss >> lastname;
		
		if(max_length < (firstname.length() + lastname.length()))
		{
			max_length = firstname.length() + lastname.length(); //keeps track of max length of names
		}
		name_t tmp(firstname, lastname);
		labscores_t score_tmp;
		while(ss >> score)
		{
			score_tmp.add_data(score);
		}
		score_map.insert(pair<name_t, labscores_t>(tmp, score_tmp));
	}
	for(map<name_t, labscores_t>::iterator it = score_map.begin(); it != score_map.end(); it++)
	{
		it->first.print_name(max_length);
		cout << " ";
		it->second.print_labscores();
		cout << endl;
	}
	return 0;
}
