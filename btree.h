#ifndef BTREE_H_
#define BTREE_H_
#include "node.h"
#include <iostream>
#include <string>
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
    void insert(std::pair<unsigned int,T> &pear);
    void split(node<T> *current);
    //getters:
    int getNumLevels();
    //functions:
    void inOrder();
    void breadthFirst();
    void breadthFirstLevel(int level);
    void breadthFirstLevels(); //for testing purposes only, horribly inefficient
    std::pair<bool,T> search(unsigned int keyValue);
    void deleteKey(unsigned int keyVal);
    void readIn(std::string textfile);
    void writeFile(std::string textfile);
private:
    //properties:
    node<T> *root;
    unsigned int degree;
    //functions:
    std::pair<bool,T> search(node<T> *nd, unsigned int keyValue); //recursive search
    void inOrder(node<T>* nd); //recursive print
    void deleteKey(unsigned int keyVal, node<T>* nd);
    void writeFile(node<T> *nd,std::string textfile,bool overwrite); //recursive write
};

#include "btree.cpp"

#endif
