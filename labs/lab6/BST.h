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
    node(int id=0);

	void print();

    TKey key;
	int ID;


	//parent info
	node *parent;
	node *left;
    node *right;
  };

	public:
		class iterator {
			public:
				iterator()
				{
					p = NULL;
				}
				//overloaded operators (++, *, ==, !=)
				void operator++();
				TKey& operator*();
				bool operator==(const iterator&);
				bool operator!=(const iterator&);
			private:
				friend class bst<TKey>;
				iterator(node *n)
				{
					p = n;
				}

				node *p;
		};

		iterator begin()
		{
			node *p = Troot;
			if(p)
			{
				while(p->left)
				{
					p = p->left;
				}
			}
		return bst<TKey>::iterator(p);

		}
		iterator end()
		{
			return bst<TKey>::iterator(NULL);
		}
  
  public:
    bst() { Troot=NULL; id = 1; node(id); }
	~bst() { clear(Troot); }

	bool empty() { return Troot==NULL; }

	void insert(TKey &);

	iterator lower_bound(const TKey &);
	iterator upper_bound(const TKey &);

	void print_bylevel();

  private:
	void clear(node *);
	node *insert(node *, TKey &);

	//ID parameter
	int id;
    node *Troot;
};
template<class TKey>
bst<TKey>::node::node(int id)
{
	ID = id;
	parent = NULL;
	left = NULL;
	right = NULL;
}
template <class TKey>
void bst<TKey>::node::print()
{
  cout << setw(3) << key << setw(4) << ID << " : ";

  if(!parent)
  {
	  cout << "ROOT ";
  }else
  {
	  cout << "P=" << setw(3) << parent->ID;
  }

  //output node and parent ID information
  //change below to output subtree ID information

  if (left)  cout << " L=" << setw(3) << left->ID;
  else       cout << "      ";
  if (right) cout << " R=" << setw(3) << right->ID;
  else       cout << "      ";

  cout << "\n";
}

//bst<TKey>::iterator functions not defined above go here
template<class TKey>
typename bst<TKey>::iterator bst<TKey>::lower_bound(const TKey &val)
{
	node *min = Troot;
	node *p = Troot;
	while(p)
	{
		if(p->key == val)
		{
			return bst<TKey>::iterator(p);
		}
		if(val < p->key)
		{
			if(p->left)
			{
				if(p->left->key == val)
				{		
					return bst<TKey>::iterator(p->left);
				}
				p = p->left;
				if((p->key >= val) && ((p->key < min->key) || (min->key < val)))

				{
					min = p;
				}
			}else //if left does not exist but it is less
			{
				p = p->right;
			}
		}
		else if(val > p->key)
		{
			if(p->right)
			{
				if(p->right->key == val)
				{
					return bst<TKey>::iterator(p->right);
				}
				p = p->right;
				if((p->key >= val) && ((p->key < min->key)|| (min->key < val)))

				{
					min = p;
				}

			}else
			{
				p = p->left;
			}
		}

		if(!p->left && !p->right)
			break;
	}

	if(min == Troot)
	{
		if(Troot->key < val)
			min = NULL;
	}


	return iterator(min);
}
template<class TKey>
typename bst<TKey>::iterator bst<TKey>::upper_bound(const TKey &val)
{

	node *max = Troot;
	node *p = Troot;
	while(p)
	{
		if(val < p->key)
		{
			if(p->left)
			{
				p = p->left;
				if((p->key > val) && ((p->key < max->key) || (max->key <= val)))
				{
					max = p;
				}
			}else //if left does not exist but it is less
			{
				p = p->right;
			}
		}
		else if(val >= p->key)
		{
			if(p->right)
			{
				p = p->right;
				if((p->key > val) && ((p->key < max->key)|| (max->key <= val)))

				{
					max = p;
				}
			}else
			{
				p = p->left;
			}
		}
		if(!p->left && !p->right)
			break;
	}

	if(max == Troot)
	{
		if(Troot->key < val)
			max = NULL;
	}


	return iterator(max);

}

template <class TKey>
void bst<TKey>::iterator::operator++()
{
	if(p->right)
	{
		p = p->right;
		while(p->left)
			p = p->left;
		return;
	}
	if(!(p->parent) && !(p->right))
	{
		p = NULL;
		return;
	}
	if(p->parent->right)
	{
	if(p->parent->right == p)
	{
		while(p->parent->right == p)
		{
			p = p->parent;
			if(!p->parent)
			{
				p = NULL;
				return;
			}
		}
	}
	}
	p = p->parent;
	return;

}

template<class TKey>
TKey& bst<TKey>::iterator::operator*()
{
	return p->key;
}

template<class TKey>
bool bst<TKey>::iterator::operator==(const iterator& rhs)
{
	if((p==NULL) && (rhs.p==NULL))
		return true;
	if(!p && rhs.p)
		return false;
	return p->key == rhs.p->key;
}

template<class TKey>
bool bst<TKey>::iterator::operator!=(const iterator& rhs)
{
	if((p==NULL) && (rhs.p==NULL))
	{

		return false;
	}
	if((p==NULL) && rhs.p)
	{
		return true;
	}
	if(p && (rhs.p==NULL))
	{
		return true;
	}
	return p->key != rhs.p->key;
}

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
  //set parent link below
	
  if (T == NULL) {
    T = new node(id++);
    T->key = key;
  } else if (T->key == key) {
    ;
  } else if (key < T->key) {
    T->left = insert(T->left, key);
	T->left->parent = T;
  } else {
    T->right = insert(T->right, key);
	T->right->parent = T;
  }

  return T;
}

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
