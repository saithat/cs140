#include <cstdlib>
#include <iostream>
#include <cstdio>

using namespace std;
const string face[] = { "Ace", "2", "3", "4", "5", "6", "7",
                        "8", "9", "10", "Jack", "Queen", "King" }; 
const string suit[] = { "Spades", "Hearts", "Diamonds", "Clubs" };

class list 
{  
	struct node 
	{
    	node(int data=0);
    	int data;
    	node *next;
  	};
  	public:
    	list();
    	~list();
    	void insert(const int &);
		friend ostream & operator<<(ostream &, const list &);
	private:
    int N;
    node *head;
};
list::node::node(int n_data) 
{
	data = n_data;
	next = NULL;
}
list::list() 
{  
	head = new node;
}
list::~list() 
{
	node *p = head->next;
	node *pp = p->next;
	while(pp->next)
	{
		delete p;
		p = pp;
		pp = pp->next;
	}
	delete p;
	delete pp;
	delete head;
 }
void list::insert(const int &din) 
{  
	node *p = new node(din);
	node *pp = head;
	p->next = pp->next;
	pp->next = p;
	while(p->next)
	{
		pp = pp->next;
		p = p->next;
		if(p->data == din)
		{
			pp->next = p->next;
			delete p;
			return;
		}
	}

}

ostream & operator<<(ostream &out, const list &v)
{
	list::node *p = v.head;
	while(p->next)
	{
		p = p->next;
		out << face[p->data] << " ";
	}
	return out;
}



string random_card(bool verbose=false) {
	
	string card;

	card = face[ rand()%13 ];
	card += " of ";
	card += suit[ rand()%4 ];

	if (verbose)
	  cout << card << "\n";

	return card;
}

int main(int argc, char *argv[])
{

	bool verbose = false;
	int seedvalue = 0;

	for (int i=1; i<argc; i++) {
	  string option = argv[i];
	  if (option.compare(0,6,"-seed=") == 0) {
	    seedvalue = atoi(&argv[i][6]);
	  } else if (option.compare("-verbose") == 0) {
	    verbose = true;
	  } else 
	    cout << "option " << argv[i] << " ignored\n";
	}

	bool stop_condition = false;

	srand(seedvalue);

	// declare a table that can keep track of the
	// cards dealt for each suit -- initialize to 0
	
	int tab[4][13] = {0};
	int star_row;

	list ranks[4];

	while (1) {
	  string card = random_card(verbose);
	char s[25];
	  char o[25];
	  char v[25];

	  // reverse engineer card suit and face (value)
	  // update accordingly: table[suit][value]++
	  sscanf(card.c_str(), "%s %s %s", &s, &o, &v);
	  
	  string group = s;
	  string value = v;

	  for(int i = 0; i < 4; i++)
	  {
		for(int j = 0; j < 13; j++)
		{
			
			if((group.compare(face[j]) == 0) && (value.compare(suit[i]) == 0))
			{
				tab[i][j] += 1;
				ranks[i].insert(j);
			}
		}
		if((tab[i][10] >= 2) && (tab[i][11] >= 2) && (tab[i][12] >= 2))
		{
			star_row = i;
			stop_condition = true;
		}
	  }
	  if(stop_condition)
	  {
		  break;
	  }
	}
      // break out of loop if stopping criteria met

	for(int i = 0; i < 4; i++)
	{
		printf("%8s : ", suit[i].c_str());
		cout << ranks[i];
		if(star_row == i)
		{
			printf("**");
		}
		printf("\n");
	}
	// print formatted table contents to stdout 
}
