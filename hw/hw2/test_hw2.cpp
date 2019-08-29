#include <iomanip>
#include <iostream>
using namespace std;
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
    bool empty() const
 	{ 
		return N == 0;
	}
    int size()   const
 	{
 	return N;
 	}
    void clear();
    void insert(int, const int &);
    void erase(int);
    void push_back(const int &);
    void pop_back();
	void push_front(const int &);
	void pop_front();
	const int & front();
    const int & back();
    int & operator[](int);
  private:
    int N;
    node *head;
    node *findnode(int);
};
list::node::node(int n_data)
 {
  data = n_data;
  next = NULL;
}
list::list()
 {
  head = new node;
  N = 0;
}
list::~list()
 {
 clear();
 delete head;
 }
void list::clear()
 { while (!empty()) erase(0); }
void list::insert(int i, const int &din)
 {
  node *p = new node(din);
  node *pp = findnode(i-1);
  p->next = pp->next;
  pp->next = p;
  N++;
}
void list::erase(int i)
 {
  node *p;
  node *pp = findnode(i-1);
  p = pp->next;
  pp->next = p->next;
  delete p;
  N--;
}
void list::push_back(const int &din)
 {
 insert(N, din);
 }
void list::pop_back()
 {
 erase(N-1);
 }
const int & list::back()
 {
  node *p = findnode(N-1);
  return p->data;
}
int & list::operator[](int i)
 {
  node *p = findnode(i);
  return p->data;
}
list::node *list::findnode(int i)
 {
  if (i == -1) return head;
  node *p = head->next;
   while (i--)
    p = p->next;
  return p;
}
void list::push_front(const int &din)
{
	node *p = new node(din);
	
	p->next = head->next;
	head->next = p;

	N++;
}
void list::pop_front()
{
	node *p;

	p = head->next;
	head->next = p->next;

	delete p;

	N--;

}
const int & list::front()
{
	node *p = head->next;
	return p->data;
}
void printlist(const char *operation, list &v)
 {
  cout << setw(14) << operation
       << " s=" << v.size()
        << " : ";
  for (int i=0; i<v.size(); i++)
     cout << " " << v[i];
  cout << "\n";
}
int main(int argc, char *argv[])
 {
  cout << left;
  list v;           printlist("list v", v);
  v.push_back(7);   printlist("v.push_back(7)", v);
  v.push_back(8);   printlist("v.push_back(8)", v);
  v.push_back(9);   printlist("v.push_back(9)", v);
  v.insert(1, 20);  printlist("v.insert(1,20)", v);
  v.erase(2);       printlist("v.erase(2)", v);
  v.insert(0, 11);  printlist("v.insert(0,11)", v);
  v.push_back(2);   printlist("push_back(2)", v);
  v.pop_back();     printlist("pop_back()", v);
  v.insert(1, 4);   printlist("v.insert(1,4)", v);
  v[1] = 5;         printlist("v[1] = 5", v);
  v.pop_front();    printlist("pop_front", v);
  v.push_front(2);	printlist("push_front(2)", v);
  v.clear();        printlist("clear()", v);
}
