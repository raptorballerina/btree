#ifndef NODE_H_
#define NODE_H_
#include <vector>
#include <algorithm> //fill
#include <iostream>

template <class T>
class node
{
public:
    /*node of degree n can have up to n children and n-1 keys
    reserve space for n keys so that vector will not resize on overflow*/
    node(unsigned int dgree);
    node(unsigned int dgree,const std::pair<unsigned int,T> &pear);
    node(unsigned int dgree,const std::pair<unsigned int,T> &pear,node<T> *left,node<T> *right);
    //getters:
    unsigned int getDegree(){return degree;}
    unsigned int getMaxKeys(){return 2 * degree - 1;}//changed
    unsigned int getNumKeys(){return keys.size();}
    unsigned int getNumChilds(){return childs.size();}
    node<T>* getParent(){return parent;}
    bool isLeaf(){return leaf;} //returns true if no children
    unsigned int getIndex(unsigned int keyValue); //returns closest index based on key
    T getData(unsigned int keyValue); //returns data from key
    node<T>* getNode(std::pair<unsigned int, T> &pear); //returns node from standard pair
    node<T>* getNode(unsigned int keyValue); //returns node from key
    //setters:
    void setParent(node<T> *nd){parent=nd;}
    //functions:
    void insert(const std::pair<unsigned int, T> &pear,node<T>* childPtr=nullptr);
        //bool deleteKey(unsigned int keyValue);
    int search(unsigned int keyValue);


    bool removeChild(unsigned int childIndex);
    void addKey(std::pair<unsigned int,T> &pear);
    void addChild(node* child);
    void insertKey(std::pair<unsigned int,T>pear,unsigned int i){keys.insert(keys.begin()+i,pear);}
    void insertChild(node* child, unsigned int i);
    void setChild(node* child, unsigned int index){childs[index] = child;}
    void setLeaf(bool val){leaf=val;}
    void insert(unsigned int keyValue, node<T> *childPtr=nullptr);

//	bool isRoot(){return root;}
    void inOrder();
	//properties:




	//overloads:
    template <class U>
        friend std::ostream& operator<< (std::ostream &out, node<T> &nd); //prints data values in node
    T operator[] (unsigned int index); //returns data value from index
private:

    //properties:
    unsigned int degree; //t, minimum number of children
    unsigned int maxKeys; //maximum keys, 2t-1
    bool leaf; //childless, true
    node<T>* parent; //parent pointer
    //objects:
    std::vector<std::pair<unsigned int,T> > keys; //vector of keys and data values
    std::vector<node<T>*> childs; //vector of child pointers
};

#include "node.cpp"

#endif
