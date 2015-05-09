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
    node(unsigned int dgree, const std::pair<unsigned int, T> &pear, node<T> *left, node<T> *right);


    //properties:
    node* parent;

    //getters:
    unsigned int getDegree() { return degree; }
    unsigned int getMaxKeys() { return 2 * degree - 1; }//changed
    unsigned int getNumKeys() { return keys.size(); }
    bool isLeaf() { return leaf; }
    unsigned int getIndex(unsigned int keyValue);
    unsigned int getData(unsigned int keyValue);
    node<T>* getNode(std::pair<unsigned int, T> &pear);
    node<T>* getNode(unsigned int keyValue);
    T getDataByKey(unsigned int keyValue);
    T getDataByIndex(unsigned int index);
    //functions:
    void insert(node *nd,const std::pair<unsigned int,T> &pear);
    //node* getNode(std::pair<unsigned int,T>  &pear);
    bool keyExists(unsigned int keyValue);
    bool deleteKey(unsigned int keyValue);
    bool removeChild(unsigned int childIndex);
    void addKey(std::pair<unsigned int,T> &pear);
    void addChild(node* child);
    void insertKey(std::pair<unsigned int,T>pear,unsigned int i){keys.insert(keys.begin()+i,pear);}
    void insertChild(node* child, unsigned int i);
    void setChild(node* child, unsigned int index){childs[index] = child;}
    void setLeaf(bool val){leaf=val;}
    void insert(unsigned int keyValue, node<T> *childPtr=nullptr);
    int search(unsigned int keyValue);
//	bool isRoot(){return root;}
    void inOrder();
	//properties:
    std::vector<std::pair<unsigned int,T> > keys;
    std::vector<node<T>*> childs;



	//overloads:
    template <class U>
        friend std::ostream& operator<< (std::ostream &out, node<T> &nd); //prints data values in node
    T operator[] (unsigned int index); //returns data value from index
private:

    //properties:
    unsigned int degree; //t, minimum number of children
    unsigned int maxKeys; //maximum keys, 2t-1
    bool leaf; //childless, true

    //objects:
	//functions:
};

#include "node.cpp"

#endif
