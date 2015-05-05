#ifndef NODE_H_
#define NODE_H_
#include <vector>
#include <algorithm> //fill

template <class T>
class node
{
public:
	/*node of degree n can have up to n children and n-1 keys
	reserve space for n keys so that vector will not resize on loose insertion*/
	node(int dgree);
	node(int dgree,std::pair<int,T> &pear);
	//properties
	node* parent;
	//getters:
	int getDegree(){return degree;}
	int getMaxKeys(){return maxKeys;}
	int getNumKeys(){return keys.size();}
	bool isLeaf(){return leaf;}
	//functions:
	void insert(node *nd,const std::pair<int,T> &pear);
	node* getNode(const std::pair<int,T> > &pear);
	int getIndex(int keyValue);
	bool keyExists(int keyValue);
	bool deleteKey(int keyValue);
	bool removeChild(int childIndex);
	void addKey(std::pair<int,T> pear){keys.add_back(pear);} 
	void insertKey(std::pair<int,T>pear,int i){keys.insert(keys.begin()+i,pear);}
	void insertChild(node* child, int i){childs.insert(childs.begin()+1, child);}
	void addChild(node* child){childs.add_back(child);}
	void setChild(node* child, int index){childs[index] = child;};
	//overloads:
	//T operator[](int index);
private:
	//properties:
	int degree; //maximum children, n
	int maxKeys; //maximum keys, n-1
	bool leaf; //childless returns true
	//objects:
	std::vector<std::pair<int,T> > keys;
	std::vector<node*> childs;
	//functions:
}

#include "node.cpp"

#endif
