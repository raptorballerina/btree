#include "btree.h"


template <class T>
void btree<T>::printLevel(int level)
{
    if (root!=nullptr) {
        node<T> *nd=root;
        unsigned int lev=(unsigned int)level;
        std::cout << "this is an attempt to print level " << level << "\n";
        for (unsigned int i=0; i<lev; i++) {
            if (nd->childs.size()>0) {
                std::cout << "  at level " << i << ": " << nd->keys.size() << " keys\n";
                std::cout << "  at level " << i << ": " << nd->childs.size() << " childs\n";
                nd=nd->childs[0];
            } else {
                std::cout << "  at level " << i << " child size is 0\n";
                return;
            }
        }
        if (nd==nullptr) {
            std::cout << "  level " << level << " does not exist in this tree\n";
        }
        std::cout << " first node in level " << level << " has " << nd->keys.size() << " keys\n";
        std::cout << " first node in level " << level << " has " << nd->childs.size() << " childs\n";
        std::cout << "Level " << level << ": ";
        for (unsigned int i=0; i<nd->keys.size(); i++) {
            std::cout << nd->keys[i].second << " ";
        }
        std::cout << "\n";
    }
}

template <class T>
void btree<T>::insert(std::pair<unsigned int,T> &pear)
{
    if (root==nullptr) {
        node<T> *nd=new node<T>(degree,pear);
        root = nd;
        std::cout << "in insert, we are creating a root\n";
        std::cout << "  root node: " << nd->keys.size() << " keys\n";
        std::cout << "  root node: " << nd->childs.size() << " childs\n";
    } else {
        node<T>* itr = root;
        unsigned int iDebug=0;
        while (!itr->isLeaf()){
            itr = itr->getNode(pear);
            iDebug++;
        }
        unsigned int idx = itr->getIndex(pear.first);
        if (idx == itr->getNumKeys()) {
            itr->addKey(pear);
            itr->addChild(nullptr);
        } else {
            itr->insertKey(pear,idx);
            itr->addChild(nullptr);
        }
        if (itr->getNumKeys() == degree) {
            //std::cout << "\n";
            std::cout << "in insert, we are not creating a root\n";
            std::cout << "  in node " << iDebug << ": " << itr->keys.size() << " keys\n";
            std::cout << "  in node " << iDebug << ": " << itr->childs.size() << " childs\n";
            split(itr);
        }
    }
}

template <class T>
std::pair<bool,T> btree<T>::search(unsigned int keyValue)
{
	if (root!=nullptr) {
        return root->search(keyValue);
    } else {
        return std::make_pair(false,T()); //return false if not found
    }   //T() is default value for templated type
}

template <class T>
void btree<T>::inOrder()
{
    if (root!=nullptr) {
        root->inOrder();
        std::cout << "\n";
    }
}

template <class T>
void btree<T>::split(node<T>* current){//current becomes left node!

std::cout << "in split before anything happens, current has " << current->keys.size() << " keys\n";
std::cout << "in split before anything happens, current has " << current->childs.size() << " childs\n";

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

    //int toRemove = current->keys.size() / 2 + 1;//how many keys to remove from current
    unsigned int k = median + 1;
    for (; k < current->keys.size(); k++) {
        current->keys.pop_back();
        current->childs.pop_back();
    } //do not need to remove last child here
std::cout << "in split, current has " << current->keys.size() << " keys\n";
std::cout << "in split, current has " << current->childs.size() << " childs\n";

    /*for (int i=0; i < toRemove; i++){//remove keys and children from current
        current->keys.pop_back();
        current->childs.pop_back();
    }//do not need to remove last child here*/
	
    /*std::cout << "in split, current has " << current->keys.size() << " keys\n";
    std::cout << "in split, current has " << current->childs.size() << " childs\n";

    std::cout << "in split, right has " << right->keys.size() << " keys\n";
    std::cout << "in split, right has " << right->childs.size() << " childs\n";*/

	if (current == root) {//if we're at the root, we have to make a new node and split into that
		if (current->parent != nullptr) printf("Root's parent is not nullptr!\n");
        //current->parent = new node<T>(degree,medianKey);//make new root
        //current->parent->addChild(current);//add current child (i.e. left)
        //current->parent->addChild(right);//add right child
        node<T> *nr=new node<T>(degree,medianKey);
        current->childs[0]=current; //constructor given standard pair creates nullptrs in index 0 & 1
        current->childs[1]=right;
        //root=nr;
    } else {
        int idxToInsert = current->parent->getIndex(medianKey.first);//get index to insert key in parent
		current->parent->insertKey(medianKey,idxToInsert);//insert key into parent
	
        //child ptr to the left of the new key is the same as before so we don't need to do anything there

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
