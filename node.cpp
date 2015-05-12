#include <limits>
#include "node.h"

#define LADYBUG 0 //set to true for debug statements

template <class T>
node<T>::node(unsigned int dgree)
{
    degree=dgree; //max number of children = 2n
    maxKeys=2 * degree - 1; //max number of keys = 2n-1
    parent=nullptr; //parent pointer defaults to null
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
    keys.reserve(2 * dgree); //reserve key vector size, needs to allow overflow by 1
    childs.reserve(2 * dgree); //reserve child pointer vector size
    keys.push_back(pear); //insert key value into key vector
    if (LADYBUG) { std::cout << "new node with key created\n"; }
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
    if (left==nullptr || right==nullptr) {
        if (LADYBUG) {
            std::cout << "warning - you are passing in a nullptr to the constructor\n";
        }
    }
    if (LADYBUG) { std::cout << "new node with key and child pointers created\n"; }
}

template <class T>
void node<T>::addChildToBack(node* child)
{
    childs.push_back(child);
}

//returns closest index based on key, used for insert or exists using binary search
template <class T>
unsigned int node<T>::getIndexToInsert(unsigned int keyValue)
{
 //   std::cout << "entered getIndexToInsert w/ keyValue " << keyValue << std::endl;
    int lo=0;
    int hi=keys.size()-1;
    unsigned int idx=0;
    while (lo<=hi) {
        idx=(lo+hi)/2;
        if (keyValue<=keys[idx].first) {//segfaulting here????????
            hi=idx-1;
        } else { //keyValue>keys[idx].first
            lo=idx+1;
        }
    }
    if (LADYBUG) {
    //    std::cout << "in get index, value " << keyValue << " at index " << lo << "\n";
    }
  //  std::cout << "leaving getIndexToInsert w/ keyValue " << keyValue << std::endl;
    return lo;
}

//returns key at index
template <class T>
int node<T>::getKeyVal(unsigned int index)
{
    if (index>=keys.size()) {
        return -1;
    }
    return (int)keys[index].first;
}

template <class T>
std::pair<unsigned int,T> node<T>::getPair(unsigned int index)
{
    if (index<keys.size()) {
        return keys[index];
    }
    if (LADYBUG) {
        std::cout << "in getPair, index " << index << " out of bounds\n";
    }
    return std::make_pair<unsigned int,T>(std::numeric_limits<unsigned int>::max(),T());
}

//returns child node pointer at index
template <class T>
node<T>* node<T>::getChild(unsigned int index)
{
//    if (LADYBUG) std::cout << "in getChild w/ index " << index << std::endl;
    if (index<childs.size()) {
        return childs[index];
    } else { //index>=childs.size()
        if (LADYBUG) {
            std::cout << "in getchild, index " << index << " out of bounds\n";
        }
        return nullptr;
    }
}

//returns data value from key value
template <class T>
T node<T>::getData(unsigned int keyValue)
{

    unsigned int index=getIndexToInsert(keyValue);
    if (index>=keys.size() || index < 0) { //check the size first so that it won't seg fault
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

//returns node pointer to traverse down
template <class T>
node<T>* node<T>::getNodeToTraverse(std::pair<unsigned int, T> &pear)
{
    unsigned int idx=getIndexToInsert(pear.first);
    return childs[idx];
}
template <class T>
node<T>* node<T>::getNodeToTraverse(unsigned int keyValue)
{
    unsigned int idx=getIndexToInsert(keyValue);
    return childs[idx];
}

/*
template <class T>
bool node<T>::deleteKey(unsigned int keyValue)
{
    int idx=getIndex(keyValue);
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
    }
    return false;
}
*/
//search by key value, return index if found, or -1 if not found
template <class T>
int node<T>::searchNode(unsigned int keyValue)
{
    unsigned int index = getIndexToInsert(keyValue);
    if (index >= keys.size()) { //check size so no seg fault
        if (LADYBUG) {
            std::cout << "in node.search, index " << index << " out of bounds\n";
        }
        return -1;
    }
    if (keyValue==keys[index].first) {
        return index;
    }
    return -1; //default to nothing found
}

template <class T>
bool node<T>::removeKey(unsigned int index)
{
    if (LADYBUG) std::cout << "Index we're trying to remove in removeKey=" << index << std::endl;
    if (LADYBUG) std::cout << "keys.size() in removeKey=" << keys.size() << std::endl;
    if (LADYBUG) std::cout << "At index " << index << ": " << keys[index].first << std::endl;
    if (index<keys.size()) {
        if (LADYBUG) std::cout << "Got inside the if in remove key!" << std::endl;
        keys.erase(keys.begin()+index);
        if (LADYBUG) std::cout << "Got past keys.erase in remove key!" << std::endl;
        return true;
    } else {
        if (LADYBUG) {
            std::cout << "in removeKey, index " << index << " is out of bounds\n";
        }
        return false;
    }
}

template <class T>
bool node<T>::removeChild(unsigned int index)
{
    if (index<childs.size()) {
        childs.erase(childs.begin()+index);
        return true;
    } else {
        if (LADYBUG) {
            std::cout << "in removeChild, index " << index << " is out of bounds\n";
        }
        return false;
    }
}
/*
//decides where in node key value should go and adds child pointer accordingly
template <class T>
void node<T>::insert(const std::pair<unsigned int, T> &pear,node<T>* childPtr)
{
    unsigned int index = getIndexToInsert(pear.first);
    keys.insert(keys.begin()+index, pear);
    if (index!=0) { //if insert index > 0, ptr goes to right of key, otherwise left
        index++;
    }
    childs.insert(childs.begin()+index, childPtr);
    if (keys.size()==1 && childs.size()==1) { //node empty to begin with, check pointers
        childs.push_back(nullptr); //set right child ptr to null
        if (LADYBUG) {
            if (childPtr!=nullptr) {
                std::cout << "inserted into empty node, set right child ptr\n";
            }
        }
    }
}
*/
template <class T>
void node<T>::insertKeyIntoNode(const std::pair<unsigned int, T> &pear){
    unsigned int index = getIndexToInsert(pear.first);
    insertKeyAtIndex(pear,index);
}

template <class T>
void node<T>::addKeyToBack(std::pair<unsigned int,T> &pear) {
    keys.push_back(pear); //add pair to key vector
}

template <class T>
void node<T>::insertKeyAtIndex(std::pair<unsigned int,T> pear, unsigned int i)
{
    if (i<keys.size()) {
        keys.insert(keys.begin()+i, pear);
    } else {
        keys.push_back(pear);
    }
}

template <class T>
void node<T>::insertChildAtIndex(node* child, unsigned int i)
{
    if (i<childs.size()) {
        childs.insert(childs.begin()+i, child);
    } else {
        childs.push_back(child);
    }
}

//print data values in a node
template <class U>
std::ostream& operator<<(std::ostream &out, node<U> &nd)
{
    for (unsigned int i=0; i<nd.keys.size(); i++) {
        std::cout << nd.keys[i].second << " ";
    }
    return out;
}

//returns reference to standard pair when given an index, read-only
template <class T>
T& node<T>::operator[](unsigned int index)
{
    if (index>=keys.size()) { //check size first so no seg fault
        if (LADYBUG) {
            std::cout << "in [] operator, index " << index << " is out of bounds\n";
        }
        index = keys.size()-1;
    }
    return keys[index].second;
}
