#ifndef BST_H
#define BST_H

#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

template <class TKey>
class bst {
  struct node {
    node(ID = default value);

	void print();

    TKey key;
	ID parameter

	parent info
	node *left;
    node *right;
  };
  
  public:
	class iterator {
	  public:
		default constructor (no argument)
		overloaded operators (++, *, ==, !=)
	  private:
	    friend class bst<TKey>;
		constructor (with argument)

	    node *p;
	};

	iterator begin() { ... }
	iterator end() { ... }

  public:
    bst() { Troot=NULL; }
	~bst() { clear(Troot); }

	bool empty() { return Troot==NULL; }

	void insert(TKey &);

	iterator lower_bound(const TKey &);
	iterator upper_bound(const TKey &);

	void print_bylevel();

  private:
	void clear(node *);
	node *insert(node *, TKey &);

	ID parameter
    node *Troot;
};

bst<TKey>::node constructor goes here

template <class TKey>
void bst<TKey>::node::print()
{
  cout << setw(3) << key << " :";

  output node and parent ID information
  change below to output subtree ID information

  if (left)  cout << " L=" << setw(3) << left->key;
  else       cout << "      ";
  if (right) cout << " R=" << setw(3) << right->key;
  else       cout << "      ";

  cout << "\n";
}

bst<TKey>::iterator functions not defined above go here

template <class TKey>
void bst<TKey>::clear(node *T)
{
  if (T) {
    clear(T->left);
    clear(T->right);
    delete T;
    T = NULL;
  }
}

template <class TKey>
void bst<TKey>::insert(TKey &key)
{ 
  Troot = insert(Troot, key);
}

template <class TKey>
class bst<TKey>::node *bst<TKey>::insert(node *T, TKey &key)
{
  set parent link below

  if (T == NULL) {
    update and set node ID 
    T = new node;
    T->key = key;
  } else if (T->key == key) {
    ;
  } else if (key < T->key) {
    T->left = insert(T->left, key);
  } else {
    T->right = insert(T->right, key);
  }

  return T;
}

bst<TKey>::lower_bound function goes here

bst<TKey>::upper_bound function goes here

template <class TKey>
void bst<TKey>::print_bylevel()
{
  if (Troot == NULL)
    return;

  queue<node *> Q;
  node *T;

  Q.push(Troot);
  while (!Q.empty()) {
    T = Q.front();
    Q.pop();

    T->print();
    if (T->left)  Q.push(T->left);
    if (T->right) Q.push(T->right);
  }
}
#endif
