#include "btree.h"

bool BUMBLEBEE=true; //set to true for debug statements

template <class T>
int btree<T>::getNumLevels()
{
    if (root==nullptr) return -1;
    node<T> *itr = root;
    int i=1;
    while (!itr->isLeaf()) {
        i++;
        itr = itr->getChild(0);
    }
    return i;
}

template <class T>
void btree<T>::deleteKey(unsigned int keyVal) {
    if (root != nullptr) {
        deleteKey(keyVal, root);
    }
}

template <class T>
void btree<T>::deleteKey(unsigned int keyVal, node<T>* nd) {
    int idx;
    if ((idx = nd->searchNode(keyVal)) != -1) {//if the key we're looking for is in current node
        if (nd->isLeaf()) {
            for (unsigned int i=0; i<nd->getNumKeys(); i++) {
                if (nd->getPair(i).first == keyVal) {//delete key
                    nd->removeKey(i);
                    nd->removeChild(i);
                }
            }
        } else {
            //if childs[i] has  <= t keys, replace the key we want to get rid of w/ last key of that node and recursively delete it from that node
            node<T>* leftChild = nd->getChild(nd->getIndex(keyVal));
            node<T>* rightChild = nd->getChild(nd->getIndex(keyVal)+1);
            std::pair<unsigned int,T> temp;
            if (leftChild->getNumKeys() >= degree){
                temp = leftChild->getPair(leftChild->getNumKeys()-1);
                nd->setKey(idx,temp);

                deleteKey(leftChild->getPair(leftChild->getNumKeys()-1).first,leftChild);
            } else if (rightChild->getNumKeys() >= degree){ //if childs[i] has < t keys, do pretty much the same thing with the right child except we get the leftmost key instead
                temp = rightChild->getPair(0);
                nd->setKey(idx,temp);
                deleteKey(rightChild->getKey(0),rightChild);
            } else {
                //if right and left children both have t-1 keys:
                //move the key we want to delete and everything in rightChild to leftChild, deleting ptr to rightChild from nd
                //recursively delete key we want to delete from leftChild
                temp = nd->getPair(idx);
                leftChild->addKey(temp);//add key to delete to left node
                for (unsigned int i=0; i < rightChild->getNumKeys(); i++) {//add rightChild's keys to leftChild
                    temp = rightChild->getPair(i);
                    leftChild->addKey(temp);
                }
                for (unsigned int i=0; i < rightChild->getNumChilds(); i++) {//add rightChild's children to leftChild
                    leftChild->addChild(rightChild->getChild(i));
                }
                nd->removeKey(idx);
                nd->removeChild(idx+1);
                delete rightChild;
                deleteKey(keyVal,leftChild);
            }
        }
    } else {//if the key we want to delete is not in the current node
        unsigned int idxToTraverse = nd->getIndex(keyVal);
        node<T>* childToCheck = nd->getChild(idxToTraverse);
        if (childToCheck->getNumKeys() >= degree)
            deleteKey(keyVal,childToCheck);
        else {//Do the same thing as above

        }
    }

}

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
        unsigned int idx = itr->getIndex(pear.first);
        while (!itr->isLeaf()){
            itr = itr->getChild(idx);
            idx = itr->getIndex(pear.first);
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
        if (current->getNumChilds()>0) { //if there are children, add them
            right->addChild(current->getChild(j));
        }
    }
    if (current->getNumChilds()>0) { //if there are children, add last child
        right->addChild(current->getChild(j));
    }
    //int toRemove = current->keys.size() / 2 + 1;//how many keys to remove from current
    int k = current->getNumKeys() - 1;
    for (; k>=median; k--) {
        if (BUMBLEBEE) {
            std::cout << "popped index " << k << ": " << current->getPair(k).second << "\n";
        }
        current->removeKey(k);
        if (right->getNumChilds()>0) { //if there are children, remove them
            current->removeChild(k);
        }
    } //do not need to remove last child here
    if (BUMBLEBEE) {
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
        /*node<T> *lft = root->getChild(0); //replaces: node<T>* lft=root->childs[0];
        if (BUMBLEBEE) {
            std::cout << "   left now has: ";
            for (unsigned int m=0; m<lft->getNumKeys(); m++) {
                std::cout << lft->getPair(m).second << " ";
            }
            std::cout << "\n";
        }
        node<T>* rght=root->getChild(1);
        if (BUMBLEBEE) std::cout << "   right now has: ";
        for (unsigned int m=0; m<rght->getNumKeys(); m++) {
           if (BUMBLEBEE) std::cout << rght->getPair(m).second << " ";
        }
        if (BUMBLEBEE) std::cout << "\n";*/
		//set roots for left and right
		current->setParent(root);
		right->setParent(root);

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
    //unsigned int level=0;
    std::queue<node<T>*> qu; //create queue & push root
    qu.push(root);
    std::cout << "| ";
    while (!qu.empty()) { //print items at front of queue & push root
        node<T> *nd = qu.front();
        unsigned int i=0;
        for (; i<nd->getNumKeys(); i++) {
            std::cout << nd->getPair(i).second << " ";
        }
        std::cout << "| ";
        qu.pop();
        for (i=0; i<nd->getNumChilds(); i++) {
            if (nd->getChild(i) != nullptr) {
                qu.push(nd->getChild(i));
            }
        }
    }
    std::cout << "\n";
}

template <class T>
void btree<T>::breadthFirstLevel(int level)
{
    if (root==nullptr) return;
    int lvl=0;
    std::queue<std::pair<node<T>*,int> > qu; //create queue
    std::pair<node<T>*,int> sp;
    sp.first = root;
    sp.second = lvl;
    qu.push(sp); //push root & level
    std::cout << level << ": | ";
    while (!qu.empty()) { //print items at front of queue
        std::pair<node<T>*,int> sp = qu.front();
        unsigned int i=0; //iterator
        if (sp.second==level) { //only print if levels match
            for (; i<sp.first->getNumKeys(); i++) {
                std::cout << sp.first->getPair(i).second << " ";
            }
            std::cout << "| ";
        }
        qu.pop();
        lvl++;
        for (i=0; i<sp.first->getNumChilds(); i++) {
            std::pair<node<T>*,int> cp;
            cp.first = sp.first->getChild(i);
            cp.second = lvl;
            qu.push(cp); //push child node & level
        }
    }
    std::cout << "\n";
}

template <class T>
void btree<T>::breadthFirstLevels()
{
    int n = getNumLevels();
    for (int i=0; i<n; i++) {
        breadthFirstLevel(i);
    }
}

template <class T>
void btree<T>::inOrder()
{
    if (root!=nullptr) {
        inOrder(root);
        std::cout << "\n";
    }
}

template <class T>
void btree<T>::inOrder(node<T>* nd)
{
    if (nd==nullptr) {
        if (BUMBLEBEE) {
            std::cout << "in inorder, nullptr found in child node\n";
        }
        return;
    }
    bool leaf = nd->isLeaf();
    unsigned int i=0;
    for (; i<nd->getNumKeys(); i++) {
        if (!leaf) {
            inOrder(nd->getChild(i));
        }
        std::cout << nd->getPair(i).second << " ";
    }
    inOrder(nd->getChild(i));
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
    if (idx <= nd->getNumKeys()) { //check size so no seg fault
        if (keyValue == (unsigned int)nd->getKey(idx)) { //return pair if key matches
            std::pair<bool,T> pear;
            pear.first = true;
            pear.second = nd->getPair(idx).second; //replaced: pear.second = nd[idx]
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
