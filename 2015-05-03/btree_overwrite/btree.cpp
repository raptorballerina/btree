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
void bTree::insert(const std::pair<int,T> &pear)
{
	node* itr = root;
	while (!itr->isLeaf()){
		itr = itr->getNode(pear);
	}
	int idx = itr->getIndex(pear.first);
	if (idx == itr->getNumKeys())
		itr->addKey(pear);
	else {
		itr->insertKey(idx,pear);
	}
	if (itr->getNumKeys == itr->getDegree)
		split(itr);
}


template <class T>
void bTree::split(nd* current){
	node* left = new node();
	node* right = new node();
	int median = keys.size() / 2;
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
