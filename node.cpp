#include "node.h"

bool LADYBUG=true;

node::node(int dgree)
{
	degree=dgree;
	maxKeys=dgree-1;
	leaf=true;
	keys.reserve(dgree);
	childs.reserve(dgree);
	std::fill(childs.begin(),childs.end(),nullptr);
}

node::node(int dgree,const std::pair<int,T> &pear)
{
	degree=dgree;
	maxKeys=dgree-1;
	leaf=true;
	keys.reserve(dgree);
	childs.reserve(dgree);
	std::fill(childs.begin(),childs.end(),nullptr);
	v.push_back(pear);
}

void node::insert(node* nd,const std::pair<int,T> &pear) //INCOMPLETE
{
	node *nd=nullptr;
	int i;
	while (!leaf) {
		nd=getNode(pear);
		i++;
		if (LADYBUG) { //such endless, very loop, wow!
			if (i>100) std::cout << "zomg u haz loop!\n";
		}
	}
	if (keys.size()==0) {
		keys.push_back(pear);
	} else if (keys.size()==maxKeys) {
		//at capacity
		//perform loose insertion
		//percolate up
	} else {
		int idx=getIndex(pear.first); 
		if (idx==keys.size()) {
			keys.push_back(pear)
		} else {
			keys.insert(v.begin()+idx,pear);
		}
	}
}

//returns node pointer to traverse down
node* node::getNode(const std::pair<int,T> > &pear)
{
	int idx=getIndex(pear.first);
	return childs[idx];
}

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
