#include "node.h"

bool LADYBUG=true;

template <class T>
node::node(int dgree)
{
	degree=dgree;//max number of children
	maxKeys=dgree-1;
	parent=nullptr;
	leaf=true;
	keys.reserve(dgree);
	childs.reserve(dgree);
	std::fill(childs.begin(),childs.end(),nullptr);
}

template <class T>
node::node(int dgree,const std::pair<int,T> &pear)
{
	degree=dgree;
	maxKeys=dgree-1;
	parent=nullptr;
	leaf=true;
	keys.reserve(dgree);
	childs.reserve(dgree);
	std::fill(childs.begin(),childs.end(),nullptr);
	v.push_back(pear);
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
template <class T>
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
	//if parent->getNumKeys() > maxKeys, call split on parent
	//
	
}


//returns node pointer to traverse down
template <class T>
node* node::getNode(const std::pair<int,T> > &pear)
{
	int idx=getIndex(pear.first);
	return childs[idx];
}

template <class T>
//return index for insert or exists using binary search
int node::getIndex(int keyValue)
{
	int lo=0;
	int hi=keys.size()-1;
	int idx;
	while (lo<=hi) {
		idx=lo+(hi-lo)/2;
		if (keyValue<=keys[idx].first) {
			hi=idx-1;
		} else { //keyValue>keys[idx].first
			lo=idx+1;
		}
	}
	if (idx>=keys.size()) {
		idx=keys.size();
	}
	return idx;
}

template <class T>
bool node::keyExists(int keyValue)

{
	int idx=getIndex(keyValue);
	//getindex returns keys.size when value greater than all keys
	if (idx==keys.size()) {
		return false;
	} else {
		return keyValue==keys[idx].first;
	}
}

template <class T>
bool node::deleteKey(int keyValue)
{
	int idx=getIndex(keyValue);
	//getindex returns keys.size when value greater than all keys
	if (idx==keys.size()) {
		if (LADYBUG) std::cout << "Key " << keyValue << " does not exist & therefore was not deleted!\n";
		return false;
	}
	if (keyValue==keys[idx].first) {
		keys.erase(vector.begin()+idx);
		return true;
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
