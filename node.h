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
    bool isLeaf(){return childs.size()==0;} //returns true if no children
    unsigned int getIndexToInsert(unsigned int keyValue); //returns closest index based on key
    int getKeyVal(unsigned int index); //returns key at index, -1 if out of bounds
    std::pair<unsigned int,T> getPair(unsigned int index);
    node<T>* getChild(unsigned int index); //returns node pointer at index

    T getData(unsigned int keyValue); //returns data from key
    node<T>* getNode(std::pair<unsigned int, T> &pear); //returns node from standard pair
    node<T>* getNode(unsigned int keyValue); //returns node from key
    //setters:
    void setParent(node<T> *nd){parent=nd;}
    //functions:
    void insert(const std::pair<unsigned int, T> &pear,node<T>* childPtr=nullptr);
        //bool deleteKey(unsigned int keyValue);
    int searchNode(unsigned int keyValue);

    bool removeKey(unsigned int index);
    bool removeChild(unsigned int index);
    void addKeyToBack(std::pair<unsigned int,T> &pear);
    void addChildToBack(node* child);
    void insertKeyAtIndex(std::pair<unsigned int,T>pear,unsigned int i){keys.insert(keys.begin()+i,pear);}
    void insertChildIntoNode(node* child, unsigned int i);
    void setChild(node* child, unsigned int index){childs[index] = child;}
    void setLeaf(bool val){leaf=val;}
    void insert(unsigned int keyValue, node<T> *childPtr=nullptr);
    void setKey(unsigned int idx, std::pair<unsigned int, T> &pear){keys[idx] = pear;}
//	bool isRoot(){return root;}
    void inOrder();

    void insertKeyIntoNode(const std::pair<unsigned int, T> &pear);

	//properties:

	//overloads:
    template <class U> //prints data values in node
        friend std::ostream& operator<< (std::ostream &out, node<T> &nd);
    T& operator[] (unsigned int index); //returns data from index

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
