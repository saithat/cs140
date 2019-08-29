/*
 * INSTRUCTOR-GIVEN TEMPLATE (Clara)
 * COSC 140: Prog 4 - Hashtables
 *
 * Description:
 *     
 *
 * Author:
 *     Name
 */

#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <cctype>
#include <fstream>
#include <sstream>

using namespace std;

typedef unsigned int uint;

// ----------------------------------------------------------------------------
// Hash Table Prototype                                                    {{{1
// ----------------------------------------------------------------------------

template <typename Tkey>
class hash_table {
	public:
		hash_table();
		void insert(const Tkey &);

	private:
		int hash(const Tkey &);
		int nextprime(int);
		int qprobe(const Tkey &);
		void resize();

		int num_inuse;
		int max_inuse;

		vector<Tkey> table;
};

// ----------------------------------------------------------------------------
// Hash Table Function Implementations                                     {{{1
// ----------------------------------------------------------------------------

template <typename Tkey>
hash_table<Tkey>::hash_table() {
	int N = 23;
	table.assign(N, Tkey());

	num_inuse = 0;
	max_inuse = N/2; // quadratic probe max value
}

template <typename Tkey>
void hash_table<Tkey>::insert(const Tkey &key) {
	int index = qprobe(key);

	if (table[index] == Tkey()) {
		table[index] = key;
		if (++num_inuse >= max_inuse)
			resize();
	}
}

template<>
int hash_table<int>::hash(const int &key) {
	return (uint)key % table.size();
}

template<>
int hash_table<float>::hash(const float &key) {
	return (uint)key % table.size();
}

template<>
int hash_table<string>::hash(const string &key) {
	uint index = 0;
	const char *c = key.c_str();

	while (*c)
		index = ((index << 5) | (index >> 27)) + *c++;

	return index % table.size();
}

template <typename Tkey>
int hash_table<Tkey>::nextprime(int N) {
	int i = 2;
	while (i * i <= N) {
		if (N % i == 0) { N++; i = 1; }
		i++;
	}

	return max(3, N);
}

template <typename Tkey>
int hash_table<Tkey>::qprobe(const Tkey &key) {
	int index = hash(key);

	int k = 0;
	while (table[index] != Tkey() && table[index] != key) {
		index += 2 * (++k) - 1;
		index = index % table.size();
	}

	return index;
}

template <typename Tkey>
void hash_table<Tkey>::resize() {
	vector<Tkey> tmp_table;

	for (int i = 0; i < (int)table.size(); i++) {
		if (table[i] != Tkey())
			tmp_table.push_back(table[i]);
	}

	int N = nextprime(2 * table.size());
	table.assign(N, Tkey());

	num_inuse = 0;
	max_inuse = N / 2;

	for (int i = 0; i < (int)tmp_table.size(); i++) {
		Tkey &key = tmp_table[i];
		table[ qprobe(key) ] = key;
		num_inuse++;
	}
}

// ----------------------------------------------------------------------------
// Main Function                                                           {{{1
// ----------------------------------------------------------------------------

int main(int argc, char **argv) {
	hash_table<string> H;

	string key;

	while (cin >> key)
		H.insert(key);
}
