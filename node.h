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
	reserve space for n keys so that vector will not resize on loose insertion*/
    node(unsigned int dgree);
    node(unsigned int dgree,const std::pair<unsigned int,T> &pear);
	//properties
	node* parent;
	//getters:
    unsigned int getDegree(){return degree;}
    unsigned int getMaxKeys(){return maxKeys;}
    unsigned int getNumKeys(){return keys.size();}
	bool isLeaf(){return leaf;}
	//functions:
    void insert(node *nd,const std::pair<unsigned int,T> &pear);
    node* getNode(std::pair<unsigned int,T>  &pear);
    unsigned int getIndex(unsigned int keyValue);
    bool keyExists(unsigned int keyValue);
    bool deleteKey(unsigned int keyValue);
    bool removeChild(unsigned int childIndex);
    void addKey(std::pair<unsigned int,T> pear){keys.push_back(pear);}
    void insertKey(std::pair<unsigned int,T>pear,unsigned int i){keys.insert(keys.begin()+i,pear);}
    void insertChild(node* child, unsigned int i){childs.insert(childs.begin()+i, child);}
    void addChild(node* child){childs.push_back(child);}
    void setChild(node* child, unsigned int index){childs[index] = child;}
//	bool isRoot(){return root;}
    std::pair<bool,T> search(unsigned int keyValue);
    void inOrder();
	//properties:
    std::vector<std::pair<unsigned int,T> > keys;
    std::vector<node<T>*> childs;
    unsigned int degree; //maximum children, n
    unsigned int maxKeys; //maximum keys, n-1
	bool leaf; //childless returns true
	//overloads:
	//T operator[](int index);
private:
	//properties:
	//objects:
	//functions:
};

#include "node.cpp"

#endif
