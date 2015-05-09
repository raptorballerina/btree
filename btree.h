#ifndef BTREE_H_
#define BTREE_H_
#include "node.h"
#include <iostream>
#include <vector>
#include <queue>


template <class T>
class btree
{
/*
Every node has at most m children.
Every non-leaf node (except root) has at least ceil(m⁄2) children.
The root has at least two children if it is not a leaf node.
A non-leaf node with k children contains k−1 keys.
All leaves appear in the same level, and carry information.
*/
public:
    btree(unsigned int dgree):root(nullptr),degree(dgree){}
    unsigned int getDegree(){return degree;}
    void split(node<T> *current);
    void insert(std::pair<unsigned int,T> &pear);
    std::pair<bool,T> search(unsigned int keyValue);
    //functions:
    void inOrder();
    //void printLevel(int level);
    void breadthFirst();
private:
    //properties:
    node<T> *root;
    unsigned int degree;
    //functions:
    std::pair<bool,T> search(node<T> *nd, unsigned int keyValue); //recursive search
};

#include "btree.cpp"

#endif
