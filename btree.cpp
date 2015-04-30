#include "btree.h"

template <class T>
void btree::insert(const std::pair<int,T> &pear)
{
	if (root==nullptr) {
		node *nd=new node(degree,pear);
		return;
	}
	//
}

template <class T>
void bTree::insert(node *nd,const std::pair<int,T> &pear)
{
	//
}

template <class T>
bool btree::search(int k)
{
	bool boo=false;
	if (root!=nullptr) {
		boo=root->search(k);
	}
	return boo;
}

template <class T>
node* btree::search(node *nd,int k){
	int i=0;
	while (i<(nd->numKeys)&&k>(nd->keys[i].second)){
		i++;
	}
	if (i<=(nd->numKeys)&&k==(nd->keys[i].second)){
		return nd->keys[i];
	}
}
