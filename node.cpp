#include "node.h"

bool LADYBUG=false; //set to true for debug statements

template <class T>
node<T>::node(unsigned int dgree)
{
    degree=dgree; //max number of children = 2n
    maxKeys=2 * degree - 1; //max number of keys = 2n-1
    parent=nullptr; //parent pointer defaults to null
    leaf=true; //leaf defaults to true for no children
    keys.reserve(2 * dgree); //reserve key vector size, needs to allow overflow by 1
    childs.reserve(2 * dgree); //reserve child pointer vector size
    if (LADYBUG) { std::cout << "new empty node created\n"; }
}

template <class T>
node<T>::node(unsigned int dgree, const std::pair<unsigned int, T> &pear)
{
    degree=dgree;
    maxKeys=2 * dgree-1;
    parent=nullptr;
    leaf=true;
    keys.reserve(2 * dgree); //reserve key vector size, needs to allow overflow by 1
    childs.reserve(2 * dgree); //reserve child pointer vector size
    keys.push_back(pear); //insert key value into key vector
    childs.push_back(nullptr); //do this twice:
    childs.push_back(nullptr); //1 key, 2 child pointers
    if (LADYBUG) { std::cout << "new node with key and child nullptrs created\n"; }
}

template <class T>
node<T>::node(unsigned int dgree, const std::pair<unsigned int, T> &pear, node<T> *left, node<T> *right)
{
    degree=dgree;
    maxKeys=2 * dgree-1;
    parent=nullptr;
    keys.reserve(2 * dgree);
    childs.reserve(2 * dgree - 1);
    keys.push_back(pear);
    childs.push_back(left); //push left node pointer first
    childs.push_back(right); //push right node pointer second
    if (left==nullptr && right==nullptr) {
        leaf=true; //leaf true if both child pointers null
    } else if (left!=nullptr && right!=nullptr) {
        leaf=false; //leaf false if both child pointers not null
    } else {
        leaf=false; //still make leaf false, but something went wrong here
        if (LADYBUG) { std::cout << "one of the constructor pointers is null, this is bad form\n"; }
    }
    if (LADYBUG) { std::cout << "new node with key and child pointers created\n"; }
}

template <class T>
void node<T>::addChild(node* child) {
    childs.push_back(child);
}

//returns node pointer to traverse down
template <class T>
node<T>* node<T>::getNode(std::pair<unsigned int, T> &pear)
{
    unsigned int idx=getIndex(pear.first);
    return childs[idx];
}
template <class T>
node<T>* node<T>::getNode(unsigned int keyValue)
{
    unsigned int idx=getIndex(keyValue);
    return childs[idx];
}

//returns index for insert or exists using binary search
template <class T>
unsigned int node<T>::getIndex(unsigned int keyValue)
{
    int lo=0;
    int hi=keys.size()-1;
    unsigned int idx=0;
    while (lo<=hi) {
        idx=(lo+hi)/2;
        if (keyValue<=keys[idx].first) {
            hi=idx-1;
        } else { //keyValue>keys[idx].first
            lo=idx+1;
        }
    }
    if (LADYBUG) {
        std::cout << "in get index, value " << keyValue << " at index " << lo << "\n";
    }
    return lo;
}

template <class T>
bool node<T>::keyExists(unsigned int keyValue)
{
    int idx=getIndex(keyValue);
    if (idx==keys.size()) {
        return false; //search value was greater than all values in keys
    } else {
        return keyValue==keys[idx].first; //return if values equal or not
    }
}

template <class T>
T node<T>::getDataByKey(unsigned int keyValue)
{
    unsigned int index=getIndex(keyValue);
    if (index>=keys.size()) { //check the size first so that it won't seg fault
        if (LADYBUG) {
            std::cout << "in getkeydata, nothing found for keyvalue " << keyValue << "\n";
        }
    } else if (keyValue!=keys[index].first) {
        if (LADYBUG) {
            std::cout << "in getkeydata, nothing found for keyvalue " << keyValue << "\n";
        }
    } else { //keyValue==keys[index].first)
       return keys[index].second;
    }
    return T(); //defaults to return as if nothing was found
}

template <class T>
T node<T>::getDataByIndex(unsigned int index)
{
    if (index>=keys.size()) { //check the size first so that it won't seg fault
        if (LADYBUG) {
            std::cout << "in getkeydata, index " << index << " is out of bounds\n";
        }
        index=keys.size()-1; //return last index position
    }
    return keys[index].second;
}

template <class T>
bool node<T>::deleteKey(unsigned int keyValue)
{
    /*int idx=getIndex(keyValue);
    //getindex returns keys.size when value greater than all keys
    if (idx==keys.size()) {
        if (LADYBUG) {
            std::cout << "Key " << keyValue << " does not exist, delete canceled\n";
        }
        return false;
    }
    if (keyValue==keys[idx].first) {
        keys.erase(keys.begin()+idx);
        return true;
    }*/
    return false;
}

template <class T>
int node<T>::search(unsigned int keyValue)
{
    int index = (int)getIndex(keyValue);
    if (index > (int)keys.size()) {
        index = (int)keys.size()-1;
    }
    if (keyValue==keys[index].first) {
        return index;
    }
    return -1; //default to nothing found
}



//decides where in node key value should go and adds child pointer accordingly, for non empty nodes
template <class T>
void node<T>::insert(unsigned int keyValue, node<T> *childPtr)
{
    unsigned int idx = getIndex(keyValue);
    keys.insert(keys.begin()+idx, keyValue);
    if (idx!=0) { //if insert index is 0, ptr goes to left of key, else right
        idx++;
    }
    childs.insert(childs.begin()+idx, childPtr);
    if (keys.size()==1) { //if node was empty to begin with, warn user
        childs.push_back(nullptr); //set right child ptr to null
        if (LADYBUG) {
            std::cout << "not a good idea to insert in empty node, set right child ptr\n";
        }
    }
}

template <class T>
void node<T>::addKey(std::pair<unsigned int,T> &pear) {
    keys.push_back(pear); //add pair to key vector
}
template <class T>
void node<T>::insertChild(node* child, unsigned int i)
{
    childs.insert(childs.begin()+i, child);
}

template <class T>
void node<T>::inOrder() {
    unsigned int i=0;
    for (;i<keys.size();i++) {
        if (!leaf) {
            if (LADYBUG) std::cout << "going down at " << keys[i].second << std::endl;
            childs[i]->inOrder();
        } else {
            if (LADYBUG) std::cout << "leaf at " << keys[i].second << std::endl;
        }
        std::cout << keys[i].second << " ";
    }
    if (!leaf) {
        childs[i]->inOrder();
    }
}

//print data values in a node
template <class U>
std::ostream& operator<< (std::ostream &out, node<U> &nd)
{
    for (unsigned int i=0; i<nd.keys.size(); i++) {
        std::cout << nd.keys[i] << " ";
    }
    return out;
}

//returns key when given an index
template <class T>
T node<T>::operator[] (unsigned int index)
{
    if (index>=keys.size()) {
        if (LADYBUG) {
            std::cout << "in [] operator, index " << index << " is out of bounds\n";
        }
        index = keys.size()-1;
    }
    return keys[index].first;
}

/*
template <class T>
T heap<T>::operator[](int index)
{
    if (index < this->currentSize) {
        return this->array[index].second;
    } else {
        return this->array[currentSize-1].second;
    }
}
*/
