#include "btree.h"

template <class T>
void btree<T>::insert(std::pair<unsigned int,T> &pear)
{
    if (root==nullptr) {
        node<T> *nd=new node<T>(degree,pear);
        root = nd;
    } else {
        node<T>* itr = root;
        while (!itr->isLeaf()){
            itr = itr->getNode(pear);
        }
        unsigned int idx = itr->getIndex(pear.first);
        if (idx == itr->getNumKeys())
            itr->addKey(pear);
        else {
            itr->insertKey(pear,idx);
        }
        if (itr->getNumKeys() == degree)
            split(itr);
    }
}

template <class T>
std::pair<bool,T> btree<T>::search(unsigned int keyValue)
{
	if (root!=nullptr) {
        return root->search(keyValue);
	} else {
        return std::make_pair(false,"");
	}
}

template <class T>
void btree<T>::inOrder()
{
    if (root!=nullptr) {
        root->inOrder();
    }
}

template <class T>
void btree<T>::split(node<T>* current){//current becomes left node!
    node<T>* right = new node<T>(degree);//make right node
	right->parent = current->parent;//set right's parent
	int median = (current->keys.size() - 1) / 2;
	std::pair <int,T> medianKey = current->keys[median];
    unsigned int j = median + 1;
    for (; j< current->keys.size(); j++) {//add right keys and children from current to right node
		right->addKey(current->keys[j]);
        right->addChild(current->childs[j]);
	}
    right->addChild(current->childs[j]);//add last child
	
	int toRemove = current->keys.size() / 2 + 1;//how many keys to remove from current
	
	for (int i=0; i < toRemove; i++){//remove keys and children from current
		current->childs.pop_back();
		current->keys.pop_back();
	}
	
	if (current == root) {//if we're at the root, we have to make a new node and split into that
		if (current->parent != nullptr) printf("Root's parent is not nullptr!\n");
        current->parent = new node<T>(degree,medianKey);//make new root
		current->parent->addChild(current);//add current child (i.e. left)
		current->parent->addChild(right);//add right child
	} else {
	
        int idxToInsert = current->parent->getIndex(medianKey.first);//get index to insert key in parent
		current->parent->insertKey(medianKey,idxToInsert);//insert key into parent
	
	//child ptr to the left of the new key is the same as before so we don't need to do anything
	  //there
	 
	 //insert right ptr into correct position in parent (idxToInsert + 1)
	 current->parent->insertChild(right,idxToInsert + 1);
	 
	 if (current->parent->getNumKeys() == degree) {//if the parent is full, we split the parent
	 	split(current->parent);
	 	}
	}
	
}
/*
template <class T>
bool btree<T>::search(int k)
{
	bool found=false;
	if (root!=nullptr) {
		found=root->search(k);
	}
	return found;
}
*/
