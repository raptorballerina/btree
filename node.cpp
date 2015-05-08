#include "node.h"

bool LADYBUG=false; //set to true for debug statements

template <class T>
node<T>::node(unsigned int dgree)
{
    degree=dgree; //max number of children = n
    maxKeys=dgree-1; //max number of keys = n-1
    parent=nullptr; //parent pointer defaults to null
    leaf=true; //leaf defaults to true for no children
    keys.reserve(dgree); //reserve key vector size, needs to allow overflow by 1
    childs.reserve(dgree); //reserve child pointer vector size
    if (LADYBUG) { std::cout << "new empty node created\n"; }
}

template <class T>
node<T>::node(unsigned int dgree, const std::pair<unsigned int, T> &pear)
{
    degree=dgree;
    maxKeys=dgree-1;
    parent=nullptr;
    leaf=true;
    keys.reserve(dgree);
    childs.reserve(dgree);
    keys.push_back(pear); //insert key value into key vector
    childs.push_back(nullptr); //do this twice:
    childs.push_back(nullptr); //1 key, 2 child pointers
    if (LADYBUG) { std::cout << "new node with key and child nullptrs created\n"; }
}

template <class T>
node<T>::node(unsigned int dgree, const std::pair<unsigned int, T> &pear, node<T> *left, node<T> *right)
{
    degree=dgree;
    maxKeys=dgree-1;
    parent=nullptr;
    keys.reserve(dgree);
    childs.reserve(dgree);
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

/* //LETTING THE TREE HANDLE THE INSERT
template <class T>
void node::insert(node* nd,const std::pair<int,T> &pear) //INCOMPLETE
{
	node *nd=nullptr;

	int i;
	while (!leaf) {
		parent = nd;
		nd=getNode(pear);
		i++;
		if (LADYBUG) { //such endless, very loop, wow!
			if (i>100) std::cout << "zomg u haz loop!\n";
		}
	}
	if (keys.size()==0) {
		keys.push_back(pear);
	} else {
		int idx=getIndex(pear.first);
		if (idx==keys.size()) {
			keys.push_back(pear)
		} else {
			keys.insert(v.begin()+idx,pear);
		}
		if (keys.size() == maxKeys)
			split(parent);
	}
}
*/
//STILL NEEDS WORK
/*template <class T>
void node::split(node* parent){
	node* left = new node();//instead of this, just use current node as left node and remove extra stuff on the right
	node* right = new node();
	int median = keys.size() / 2;//index of median
	std::pair<int,T> medianKey;
	int i = 0;
	for (i=0; i < median; i++) {//insert keys and child ptrs into left node
		left->addKey(keys[i]);
		left->addChild(childs[i]);
	}
	left->addChild(childs[i]);//add last child b/c there is always one more child than keys
	int j = median + 1;
	for (; j < keys.size(); j++) {//insert keys and child ptrs into right node
		right->addKey(keys[i]);
		right->addChild[childs[j]);
	}
	right->addChild[childs[j]];

	//Insert medianKey into correct place in parent
	//use getindex and insert on parent

	//insert left and right child ptrs into correct place in parent
	//left ptr is same index as above, right ptr is that index + 1
	//need to "move over"
	//if parent->getNumKeys() > maxKeys, call split on parent


}*/

/* Lol we don't need this either
//version that uses current node as left node
void node::split(){//doesn't need to pass in parent ptr because parent ptr is attribute of node



	//need to check if we're at root here and do a separate thing for that



	node* right = new node(degree);
	int median = (keys.size()-1) / 2;
	std::pair<int,t> medianKey = keys[median];
	
	int j = median + 1;
	for (; j < keys.size(); j++) {
		right->addKey(keys[i]);
		right->addChild(childs[j]);
	}
	right->addChild[childs[j];
	
	//remove extra keys and child ptrs from current (left) here
	//we remove (numKeys / 2 + 1) keys and children from back
	int toRemove = keys.size() / 2 + 1;
	for (int i = 0; i < toRemove; i++){
		childs.pop_back();
		keys.pop_back();
	}
	
	
	//if current node is root, we make a new node
	//put the median and the left and right child ptrs into it and we're done
	if (parent == nullptr) {
		parent = new node(degree,medianKey);
		
	}
		
	
	
	int idxToInsert = parent->getIndex(medianKey.first);//get index to insert key in parent
	parent->insertKey(mediankey,idxToInsert);//insert key into parent
	
	//child ptr to left of the key you just inserted is the same as before, so we don't need to
	//	do anything there
	
	//insert right ptr into position in parent (idxToInsert + 1)
	parent->insertChild(right,idxToInsert + 1);
	



	if (parent->getNumKeys() == parent->getDegree()) 
		parent->split();
	
}*/

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
T node<T>::getKeyData(unsigned int keyValue)
{
    unsigned int idx=getIndex(keyValue);
    if (idx>=keys.size()) {
        if (LADYBUG) std::cout << "in getkeydata, nothing found for keyvalue " << keyValue << "\n";
    }
    if (keyValue!=keys[idx].first) {
        if (LADYBUG) std::cout << "in getkeydata, nothing found for keyvalue " << keyValue << "\n";
    } else { //keyValue==keys[idx].first)
       return keys[idx].second;
    }
    return T(); //defaults to return as if nothing was found
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
}

template <class T>
std::pair<bool, T> node<T>::search(unsigned int keyValue)
{
    /*std::pair<bool,T> pear; //return object
    unsigned int idx=getIndex(keyValue);
    if (keys[i].first==keyValue) {
        return std::make_pair(true, keys[i].second);
    } else {
        return childs[i]->
    if (idx==keys.size()) {
        //go down tail pointer
        //return std::make_pair(false, T());
    }*/

    /*unsigned int i=0;
    while (i<keys.size() && keyValue>keys[i].first) {
        i++; //increment iterator until end of keys or search < = actual key value
    }
    if (keys[i].first==keyValue) { //value found, return true/templated object
        pear = std::make_pair(true,keys[i].second);
    }
    if (leaf) { //if this node is a leaf, could not find value
        pear = std::make_pair(false,T());
    }
    pear = childs[i]->search(keyValue); //go to the next child node
    return pear;*/
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
        if (LADYBUG) { std::cout << "not a good idea to insert in empty node, set right child ptr\n"; }
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
