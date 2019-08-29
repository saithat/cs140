#include <iostream>
#include <cstdio>
#include <ctype.h>
#include <string>

using namespace std;

string encode (string const& line, int map)
{
	string result;
	for(int i = 0; i < (line).length(); i++)
	{
		if(isupper(line[i]))
		{
			result += char((((line[i] + map)-65) % 26)+65); //add the encryption_value to the char, subtract by 65 to change the range to 0-25 to mod by 26 and add 65 again to get the char
		}
		else if(islower(line[i]))
		{
			result += char((((line[i] + map)-97) % 26)+97);
		}
		else if(isalpha(line[i]))
		{
			result += char((((line[i] + map)-48) % 10)+48);
		}
		else{
			result += line[i];
		}
	}
	return result;
};

string decode(string const& line, int map)
{
	string result;
	for(int i = 0; i < line.length(); i++)
	{
		if(isupper(line[i]))
		{
			result += char((((line[i] - 65)+(26 - (map % 26)))%26)+65); //kinda the same thing as encode except map % 26 makes sure there can't be negatives stuff to mod
					
		}
		else if(islower(line[i]))
		{
			result += char((((line[i] - 97)+(26 - (map % 26)))%26)+97);
		}
		else if(isalpha(line[i]))
		{
			result += char((((line[i] - 48)+(26 - (map % 26)))%26)+48);
		}
		else{
			result += line[i];
		}
	}
	return result;

};

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		cerr << "Inappropiate number of args" << endl;
		return -1;
	}

	bool enc;
	if(string(argv[1]) != "-encode")
	{
		if(string(argv[1]) != "-decode")
		{
			cerr << "Can't recognize 2nd argument" << endl;
			return -1;
		}
		else
		{
			enc = false;
		}
	}
	else 
	{
		enc = true;
	}
	if(isdigit(*argv[2]) == 0)
	{
		cerr << "Enter a decimal number for arg 3" << endl;
		return -1;
	}

	int map_value;
	map_value = *argv[2] - 48;

	string line;
	if(enc)
	{
		while(cin)
		{
			getline(cin, line);
			cout << encode(line, map_value) << "\n";
		}
	}
	else
	{
		while(cin)
		{
			getline(cin, line);
			cout << decode(line, map_value) << "\n";
		}
	
	}
	return 0;

}
