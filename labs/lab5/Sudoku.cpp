#include <cstdlib>
#include <cstring>
#include <ctime>
#include <iostream>
#include <fstream>
#include <vector>
#include <thread>
#include <chrono>
using namespace std;

class sudoku {
  public:
	sudoku();

	void solve();

    void read(const char *);
    void write(const char *);
    void write(const char *, const char *);

  private:
    int solve(int, int);

    // various support functions 
    bool error_check_value(int, bool);
    bool error_check_uniqueness(int, int);

	vector<int> valid_values(int, int);
	
	vector<int> next_indices(int, int);

    void display();

    int game[9][9];
};

sudoku::sudoku() { 
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++)
      game[i][j] = 0;
  }
}

void sudoku::solve() {
  cout << "SOLVE\n";
  bool made_it = false;
	bool error = false;
	vector<int> tmp;
  // call recursive computation
	tmp = next_indices(0, 0);
	int y = tmp.back();
	tmp.pop_back();
	int x = tmp.back();
	tmp.pop_back();
	if(solve(x, y) == 0)
	error = true;

  display();
  
  // error check data values
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(!error_check_value(game[i][j], 1))
			{
				cerr << " " << i << " " << j << " " << game[i][j] << " " << "out-of-range value " << endl;
				error = true;
			}
			if(!error_check_uniqueness(i, j))
			{
				cerr << " " << i << " " << j << " " << game[i][j] << " " << "out-of-bounds grid index " << endl;
				error = true;
			}
		}
	}
  // error check uniqueness
  // exit if errors detected
  if(error)
	  exit(0);
}
bool sudoku::error_check_uniqueness(int x, int y)
{
	int val = game[x][y];
	int count = 0;
	for(int row = 0; row < 9; row++)
	{
		if(game[x][row] == val)
			count++;
		if(count > 1)
			return false;
	}
	count = 0;

	for(int col = 0; col < 9; col++)
	{
		if(game[col][y] == val)
			count++;
		if(count > 1)
			return false;
	}
	count = 0;
	int col = ((y/3)*3);
	int row ((x/3)*3); //starts at beginning of each block
	for(int i = col; i < (col + 2); i++)
	{
		for(int j = row; j < (row + 2); j++)
		{
			if(game[i][j] == val)
				count++;
			if(count > 1)
				return false;
		}
	}
	return true;

}
bool sudoku::error_check_value(int v, bool solving)
{
	if(solving)
	{
		return (v >= 1 && v <= 9);
	}
	return (v >= 0 && v <= 9);
}

void sudoku::read(const char *fname) {
  cout << "READ\n";
  bool bad_grid = false;
  int line_c = 0;
  ifstream fin(fname);
    
  int i, j, v;

  while (fin >> i >> j >> v) {
    // error check grid indices
	line_c++;
	
	if(!(i >= 0 && i <= 8 && j >= 0 && j <= 8))
	{
		cerr << "line " << line_c << ": " << i << " " << j << " " << v << " " << "out-of-bounds grid index " << endl;
		bad_grid = true;
	}else
	{
		game[i][j] = v;
	}
  }

  fin.close();

  // exit if bad grid indices
	if(bad_grid){
		exit(0);
	}
	bad_grid = false;
	display();
  // error check data values
  // error check uniqueness
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(!error_check_value(game[i][j], false))
		{
			cerr << "cell " << i << " " << j << ": out-of-bounds data value " << game[i][j] << endl;
			bad_grid = true;
		}

			if(game[i][j] != 0)
			{
			if(!error_check_uniqueness(i, j))
			{
				cerr << "cell " << i << " " << j << ": non-unique value " << game[i][j] << endl;
				bad_grid = true;
			}
			}
		}
	}
  // exit if errors detected
  if(bad_grid)
	  exit(0);
}

void sudoku::write(const char *fname) {
  ofstream fout(fname);

  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
      if (0 < game[i][j]) {
        fout << i << " "
			 << j << " "
		     << game[i][j] << "\n";
      }
    }
  }

  fout.close();
}

void sudoku::write(const char *fname, const char *addon) {
  int N1 = strlen(fname);
  int N2 = strlen(addon);

  char *n_fname = new char[N1+N2+2];

  // strip .txt suffix, then concatenate _addon.txt
  strncpy(n_fname, fname, N1-4);
  strcpy(n_fname+N1-4, "_");
  strcpy(n_fname+N1-3, addon);
  strcpy(n_fname+N1-3+N2, ".txt");

  write(n_fname);

  delete [] n_fname;
}

void sudoku::display() {
  cout << "| --------------------------- |\n";
  for (int i=0; i<9; i++) {
    for (int j=0; j<9; j++) {
	  if (j == 0) 
	    cout << "| " << game[i][j];
	  else if (j%3 == 0) 
	    cout << " | " << game[i][j];
	  else
	    cout << "  " << game[i][j];
	}
    cout << " |\n";
	if (i%3 == 2)
      cout << "| --------------------------- |\n";
  }
}
vector<int> sudoku::valid_values(int x, int y)
{
	vector<int> valid;
	bool possible = true;
	for(int val = 1; val < 10; val++)
	{
		for(int col = 0; col < 9; col++)
		{
			if(game[x][col] == val)
			{
				possible = false;
			}
		}

		for(int row = 0; row < 9; row++)
		{
			if(game[row][y] == val)
			{
				possible = false;
			}
		}
		int col = ((y/3)*3);
		int row ((x/3)*3);
		for(int i = row; i < (row + 3); i++)
		{
			for(int j = col; j < (col + 3); j++)
			{
				if(game[i][j] == val)
					possible = false;
			}
		}
		if(possible)
			valid.push_back(val);

		possible = true;
	}

	return valid;

}
vector<int> sudoku::next_indices(int x, int y)
{
	vector<int> indices;
	int cur_size = 2147483647;
	int cur_x = -1;
	int cur_y = -1;
	for(int i = 0; i < 9; i++)
	{
		for(int j = 0; j < 9; j++)
		{
			if(game[i][j] == 0)
			{
				int tmp_size = valid_values(i, j).size();
				if(tmp_size < cur_size)
				{
					cur_size = tmp_size;
					cur_x = i;
					cur_y = j;
				}
			}
		}
	}
	indices.push_back(cur_x);
	indices.push_back(cur_y);
	return indices;


}
int sudoku::solve(int x, int y) {
  // if solution found, 
  //   return solution-found
  //
  // set cell index (i,j)
  // determine valid values 
  // if no valid values left,
  //   return road-to-nowhere
  //
  // iterate thru valid values 
  //   game[i][j] = next value
  //   if solve(arguments) == solution-found
  //     return solution-found
  //
  // reset: game[i][j] = 0
  // return road-to-nowhere

	bool zero = false;
	vector<int> tmp;
	tmp = next_indices(x, y);
	int col = tmp.back();
	tmp.pop_back();
	int row = tmp.back();
	tmp.pop_back();

	if(row == -1 && col == -1)
		return 1;

	vector<int> valids = valid_values(row, col);

	if(valids.empty())
	{
		return 0; //0 is nowhere
	}
	for(vector<int>::iterator it = valids.begin(); it != valids.end(); it++)
	{
		game[row][col] = *it;
		if(solve(row, col) == 1)
		{
			return 1; //1 is solution found
		}
	}

	game[row][col] = 0;
	return 0;
}

int main(int argc, char *argv[]) {
  srand(time(NULL));

  if ((argc != 3) ||
      (strcmp(argv[1], "-s") != 0) ||
	  strstr(argv[argc-1], ".txt") == NULL) {
    cerr << "usage: Sudoku -s game.txt\n";
	exit(0);
  }

  sudoku sudoku_game;

  if (strcmp(argv[1], "-s") == 0) {
    sudoku_game.read(argv[2]);
    sudoku_game.solve();
    sudoku_game.write(argv[2], "solved");
  }
}
