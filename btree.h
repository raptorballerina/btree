#ifndef BTREE_H_
#define BTREE_H_
#include <vector>
#include "node.h"
#include <iostream>


template <class T>
class btree
{
public:
	btree(int dgree,bool preEmptiveSplit=false):root(nullptr),degree(dgree),preSplit(preEmptiveSplit){}
	int getDegree(){return degree;}
    void split(node<T> *current);
    void insert(std::pair<int,T> &pear);
//	bool find(std::pair<int,T>
private:
    node<T> *root;
	int degree;
	bool preSplit;
};

#include "btree.cpp"

#endif

//Vanessa Vanessa Vanessa!
//Ryan Ryan Ryan!!
