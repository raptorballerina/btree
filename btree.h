#ifndef BTREE_H_
#define BTREE_H_
#include "node.h"
#include <iostream>
#include <vector>
#include <queue>


template <class T>
class btree
{
public:
    btree(unsigned int dgree):root(nullptr),degree(dgree){}
    unsigned int getDegree(){return degree;}
    void split(node<T> *current);
    void insert(std::pair<unsigned int,T> &pear);
    std::pair<bool,T> search(unsigned int keyValue);
    void inOrder();
    //void printLevel(int level);
    void breadthFirst();
private:
    node<T> *root;
    unsigned int degree;
};

#include "btree.cpp"

#endif
