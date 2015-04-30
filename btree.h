#ifndef BTREE__H_
#define BTREE_H_
#include <vector>
#include "node.h"

template <class T>
class btree
{
public:
	btree(int dgree,bool preEmptiveSplit=false):root(nullptr),degree(dgree),preSplit(preEmptiveSplit){}
	int getDegree(){return degree;}
	void insert(const std::pair<int,T> &pear);
	bool find(std::pair<int,T>
private:
	node *root;
	int degree;
	bool preSplit;
}

#include "btree.cpp"

#endif

