#ifndef BTREE_H_
#define BTREE_H_
#include <vector>
#include "node.h"
#include <iostream>


template <class T>
class btree
{
public:
    btree(unsigned int dgree,bool preEmptiveSplit=false):root(nullptr),degree(dgree),preSplit(preEmptiveSplit){}
    unsigned int getDegree(){return degree;}
    void split(node<T> *current);
    void insert(std::pair<unsigned int,T> &pear);
    std::pair<bool,T> search(unsigned int keyValue);
	void inOrder();
    void printRoot();
private:
    node<T> *root;
    unsigned int degree;
	bool preSplit;
};

#include "btree.cpp"

#endif
