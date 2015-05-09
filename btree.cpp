#include "btree.h"

bool BUMBLEBEE=true; //set to true for debug statements

template <class T>
void btree<T>::insert(std::pair<unsigned int,T> &pear)
{
    if (root==nullptr) {
        node<T> *nd = new node<T>(degree,pear);
        root = nd;
        if (BUMBLEBEE) {
            std::cout << "in insert, we are creating a root\n";
            std::cout << "  root node: " << nd->getNumKeys() << " keys, " <<
                         nd->getNumChilds() << " childs\n";
        }
    } else {
        node<T>* itr = root;
        unsigned int idx=0;
        while (!itr->isLeaf()){
            idx = itr->getIndex(pear.first);
            itr = itr->getChild(idx);
        }
        if (idx == itr->getNumKeys()) {//if idx > rest of node, just push it to the back of the vector
            itr->addKey(pear);
        } else {
            itr->insertKey(pear,idx);//insert key in the correct position
        }
        if (itr->getNumKeys() > itr->getMaxKeys()) {//if too many keys in node, split
            if (BUMBLEBEE) {
                std::cout << "in insert, we are not creating a root\n";
                std::cout << "  in node: " << itr->getNumKeys() << " keys, " <<
                             itr->getNumChilds() << " childs\n";
            }
            split(itr);
        }
    }
}

template <class T>
void btree<T>::split(node<T>* current)//current becomes left node!
{
    if (BUMBLEBEE) {
        std::cout << "in split (begin), current has " << current->getNumKeys() <<
                     " keys, " << current->getNumChilds() << " childs\n";
    }
    node<T>* right = new node<T>(degree);//make right node
    right->setParent(current->getParent());//set right parent
    int median = (current->getNumKeys() - 1) / 2;
    std::pair<unsigned int,T> medianKey = current->getPair(median);
    unsigned int j = median + 1;
    for (; j< current->getNumKeys(); j++) {//add right keys and children from current to right node
        std::pair<unsigned int,T> sp = current->getPair(j);
        right->addKey(sp);
        if (right->getNumChilds()>0) { //if there are children, add them
            right->addChild(current->getChild(j));
        }
    }
    if (right->getNumChilds()>0) { //if there are children, add last child
        right->addChild(current->getChild(j));
    }

    //int toRemove = current->keys.size() / 2 + 1;//how many keys to remove from current
    unsigned int k = median - 1;
    for (; k <= current->getNumKeys(); k++) {
        if (LADYBUG) {
            std::cout << "popped index " << k << ": " << current->getPair(k).second << "\n";
        }
        current->removeKey(current->getNumKeys() - 1); //remove last key
        if (right->getNumChilds()>0) { //if there are children, remove them
            current->removeChild(current->getNumChilds()-1);
        }
    } //do not need to remove last child here
    if (LADYBUG) {
        std::cout << "in split, current has " << current->getNumKeys() << " keys, " <<
                     current->getNumChilds() << " childs\n";
    }
    /*for (int i=0; i < toRemove; i++){//remove keys and children from current
        current->keys.pop_back();
        current->childs.pop_back();
    }//do not need to remove last child here*/

    /*std::cout << "in split, current has " << current->keys.size() << " keys\n";
    std::cout << "in split, current has " << current->childs.size() << " childs\n";

    std::cout << "in split, right has " << right->keys.size() << " keys\n";
    std::cout << "in split, right has " << right->childs.size() << " childs\n";*/

    if (current == root) {//if we're at the root, we have to make a new node and split into that
        if (current->getParent() != nullptr) printf("Root's parent is not nullptr!\n");
        //current->parent = new node<T>(degree,medianKey);//make new root
        //current->parent->addChild(current);//add current child (i.e. left)
        //current->parent->addChild(right);//add right child
        node<T> *nr=new node<T>(degree,medianKey);
        root=nr;
        root->addChild(current);
        root->addChild(right);
        //removed set leaf, node isLeaf() function checks this for us
        node<T> *lft = root->getChild(0); //replaces: node<T>* lft=root->childs[0];
        if (LADYBUG) std::cout << "   left now has: ";
        for (unsigned int m=0; m<lft->getNumKeys(); m++) {
            std::cout << lft->getPair(m).second << " ";
        }
        if (LADYBUG) std::cout << "\n";
        node<T>* rght=root->getChild(1);
        if (LADYBUG) std::cout << "   right now has: ";
        for (unsigned int m=0; m<rght->getNumKeys(); m++) {
           if (LADYBUG) std::cout << rght->getPair(m).second << " ";
        }
        if (LADYBUG) std::cout << "\n";


    } else {
        //current->parent->setLeaf(false);
        unsigned int idxToInsert = current->getParent()->getIndex(medianKey.first);//get index to insert key in parent
        current->getParent()->insertKey(medianKey,idxToInsert);//insert key into parent
        //child ptr to the left of the new key is the same as before so we don't need to do anything there

        //insert right ptr into correct position in parent (idxToInsert + 1)
        current->getParent()->insertChild(right,idxToInsert + 1); //insert child in parent
        //if the parent is full, we split the parent
        if (current->getParent()->getNumKeys() > current->getParent()->getMaxKeys()) {
            split(current->getParent());
        }
    }
}

template <class T>
void btree<T>::breadthFirst()
{
    if (root==nullptr) return;
    std::queue<node<T>*> qu; //create queue & push root
    qu.push(root);
    std::cout << " | ";
    while (!qu.empty()) { //print items at front of queue & push root
        node<T> *nd = qu.front();
        unsigned int i=0;
        for (; i<nd->getNumKeys(); i++) {
            std::cout << nd->getPair(i).second << " ";
        }
        std::cout << " | ";
        qu.pop();
        for (i=0; i<nd->getNumChilds(); i++) {
            if (nd->getChild(i) != nullptr) {
                qu.push(nd->getChild(i));
            }
        }
    }
    std::cout << "\n";
}

//NEEDS WORK!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
template <class T>
void btree<T>::inOrder()
{
    if (root!=nullptr) {
        root->inOrder();
        std::cout << "\n";
    }
}

template <class T>
std::pair<bool,T> btree<T>::search(unsigned int keyValue)
{
    if (root!=nullptr) {
        return search(root, keyValue);
    } else {
        return std::make_pair<bool,T>(false,T()); //return false & default T if no root
    }
}

template <class T>
std::pair<bool,T> btree<T>::search(node<T>* nd, unsigned int keyValue)
{
    if (nd==nullptr) {
        return std::make_pair<bool,T>(false, T());
    }
    unsigned int idx = nd->getIndex(keyValue); //get closest index to key value
    if (idx <= nd->getNumKeys) { //check size so no seg fault
        if (keyValue == nd->getKey(idx)) { //return pair if key matches
            std::pair<bool,T> pear;
            pear.first = true;
            pear.second = nd[idx];
            return pear;
        } else { //traverse down appropriate node
            return search(nd->getChild(idx), keyValue);
        }
    } else { // idx > nd->getNumKeys
        if (BUMBLEBEE) {
            std::cout << "in search, getindex stepped out of bounds\n";
        }
        return std::make_pair<bool,T>(false,T());
    }
}
