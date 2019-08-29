#include <cstdio>
#include <sstream>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <cmath>
#include <cstring>
using namespace std;

typedef unsigned int uint;

class hash_table 
{
		public:    
		hash_table(bool);
		~hash_table();
		void insert(const string &, uint);
		const vector<int> & find(const string &);
		bool collect;
		int collisions;
		private:    
		int hash(const string &);    
		int nextprime(int);
		int qprobe(const string &, bool);    
		void resize();    
		struct key_line
		{
			string key;
			vector<int> lnums;
			bool inuse()
			{
				return !key.empty();
			}
			bool operator==(string k)
			{
				if (key.compare(k)==0)
					return true;
				return false;
			}
		};
		int num_inuse;    
		int max_inuse;
		vector<key_line> table;
};
hash_table::hash_table(bool coll) 
{  
	int N = 23;
	table.assign(N, key_line());
	collect = coll;
	collisions = 0;
	num_inuse = 0;
	max_inuse = N/2; // quadratic probe max value
}
hash_table::~hash_table()
{
	if(collect)
	{
		cout << "Run stats ..." << endl;
		cout << "Number of slots used: " << num_inuse << endl;
		cout << "Max number of slots: " << max_inuse << endl;
		cout << "Number of collisions: " << collisions << endl;
	}
}
void hash_table::insert(const string &key, uint lin) 
{  
	int index = qprobe(key, collect);
	
	if (!table[index].inuse()) 
	{    
		table[index].key = key;

		if (++num_inuse >= max_inuse)
		{
			resize();
			index = qprobe(key, false);
		}
	
	}
	vector<int>::iterator it;
	it = std::find(table[index].lnums.begin(), table[index].lnums.end(), lin);

	if(it == table[index].lnums.end())
	{
		table[index].lnums.push_back(lin);
	}

}
const vector<int> & hash_table::find(const string &key)
{
	int index = qprobe(key, false);
	return table[index].lnums;
}

int hash_table::hash(const string &key) 
{  
	uint index = 0;   
	const char *c = key.c_str();  
	while (*c)
		index = ((index << 5) | (index >> 27)) + *c++;  
	return index % table.size();
}
int hash_table::nextprime(int N) 
{  
	int i = 2;  
	while (i*i <= N) 
	{    
		if (N%i == 0) 
		{ 
			N++; 
			i = 1; 
		}    
		i++;  
	}  
	return max(3,N);
}

int hash_table::qprobe(const string &key, bool ifcol) 
{
	int index = hash(key);  
	int k = 0;  
	while (table[index].inuse() && !(table[index]==key)) 
	{    
		index += 2*(++k) - 1;    
		index = index % table.size();
		if(ifcol)
		{
			collisions++;
		}
	}  
	return index;
}
void hash_table::resize() 
{  

	vector<key_line> tmp_table;
	for (int i=0; i<table.size(); i++) 
	{    
		if (table[i].inuse())      
			tmp_table.push_back(table[i]);  
	}  
	int N = nextprime(2*table.size());  
	table.assign(N, key_line());   
	num_inuse = 0;  
	max_inuse = N/2;  
	for (int i=0; i<tmp_table.size(); i++) 
	{    
		key_line &key = tmp_table[i];    
		table[ qprobe(key.key, false) ] = key;    
		num_inuse++;
	}
}
char replace_punctuation(const char &c)
{
	if(ispunct(c)!=0)
	{
		return ' ';
	}
	return c;
}
int main(int argc, char *argv[]) 
{  
	string key;
	bool collect = false;
	if(argc == 3 && ((strcmp(argv[1], "-f")==0) || (strcmp(argv[1], "-vf")==0)))
	{	
		if(strcmp(argv[1], "-vf")==0)
		{
			collect = true;
		}
	}
	else
	{
		cerr << "Usage: ./Hashtable -f textfile" << endl;
		return -1;
	}
	hash_table H(collect);
	ifstream infile(argv[2]);
	string line;	
	vector<string> olines;
	vector<string> flines;
	if(infile.is_open())
	{
		while(getline(infile,line))
		{
			olines.push_back(line);
			transform(line.begin(), line.end(), line.begin(), replace_punctuation);
			flines.push_back(line);
		}
	}
	else
	{
		cerr << "Error opening file" << endl;
	}
		
	uint count = 1;
	for(vector<string>::iterator it = flines.begin();  it != flines.end(); it++)
	{
		istringstream ss(*it);
		while(ss)
		{
			string word;
			ss >> word;
			if(!word.empty())
			{
				H.insert(word, count);
			}
		}
		count++;
	}
	infile.close();
	
	cout << "find> ";
	while(cin >> key)
	{
		vector<int> lines = H.find(key);
		for(vector<int>::iterator it = lines.begin(); it != lines.end(); it++)
		{
			cout << *it << ": " << olines.at(*it-1) << endl;
		}
		cout << "find> ";
	}
	
}

