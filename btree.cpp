#include "btree.h"
#include <fstream> //ifstream
#include <sstream> //stringstream

bool BUMBLEBEE=true; //set to true for debug statements

template <class T>
int btree<T>::getNumLevels()
{
    if (root==nullptr) return -1;
    node<T> *itr = root;
    int i=1;
    while (!itr->isLeaf()) {
        i++;
        itr = itr->getChild(0);
    }
    return i;
}

template <class T>
void btree<T>::deleteKey(unsigned int keyVal) {
    if (root != nullptr) {
        deleteKey(keyVal, root);
    }
}

template <class T>
void btree<T>::deleteKey(unsigned int keyVal, node<T>* nd) {//need special case for deletion from root
    unsigned int idx;
    if ((idx = nd->searchNode(keyVal)) != -1) {//if the key we're looking for is in current node
        if (nd->isLeaf()) {
            for (unsigned int i=0; i<nd->getNumKeys(); i++) {
                if (nd->getPair(i).first == keyVal) {//delete key
                    nd->removeKey(i);
                    nd->removeChild(i);
                }
            }
        } else {
            //if childs[i] has  <= t keys, replace the key we want to get rid of w/ last key of that node and recursively delete it from that node
            node<T>* leftChild = nd->getChild(nd->getIndexToInsert(keyVal));
            node<T>* rightChild = nd->getChild(nd->getIndexToInsert(keyVal)+1);
            std::pair<unsigned int,T> temp;
            if (leftChild->getNumKeys() >= degree){
                temp = leftChild->getPair(leftChild->getNumKeys()-1);
                nd->setKey(idx,temp);

                deleteKey(leftChild->getPair(leftChild->getNumKeys()-1).first,leftChild);
            } else if (rightChild->getNumKeys() >= degree){ //if childs[i] has < t keys, do pretty much the same thing with the right child except we get the leftmost key instead
                temp = rightChild->getPair(0);
                nd->setKey(idx,temp);
                deleteKey(rightChild->getKeyVal(0),rightChild);
            } else {
                //if right and left children both have t-1 keys:
                //move the key we want to delete and everything in rightChild to leftChild, deleting ptr to rightChild from nd
                //recursively delete key we want to delete from leftChild
                temp = nd->getPair(idx);
                leftChild->addKeyToBack(temp);//add key to delete to left node
                for (unsigned int i=0; i < rightChild->getNumKeys(); i++) {//add rightChild's keys to leftChild
                    temp = rightChild->getPair(i);
                    leftChild->addKeyToBack(temp);
                }
                for (unsigned int i=0; i < rightChild->getNumChilds(); i++) {//add rightChild's children to leftChild
                    leftChild->addChildToBack(rightChild->getChild(i));
                }
                nd->removeKey(idx);
                nd->removeChild(idx+1);
                delete rightChild;
                deleteKey(keyVal,leftChild);
                if(nd == root && nd->getNumKeys() == 0) {
                    //nd is the root and has no keys, we make its child the new root
                    root = root->getChild(0);
                    delete root->getParent();
                    root->setParent(nullptr);
                }
            }
        }
    } else {//if the key we want to delete is not in the current node
        unsigned int idxToTraverse = nd->getIndexToInsert(keyVal);
        node<T>* child = nd->getChild(idxToTraverse);
        if (child->getNumKeys() >= degree)
            deleteKey(keyVal,child);
        else {
            /*if a node to the left or right of child has >= t keys, move a key from nd down to into
             *child, move a key from the left/right sibling into nd, and move the correct
             *child ptr from the left or right into child */

            if ((nd->getChild(idxToTraverse-1) != nullptr)
                    && (nd->getChild(idxToTraverse-1)->getNumKeys() >= degree)) {
                node<T>* leftSibling = nd->getChild(idxToTraverse-1);
                //move key at idxToTraverse in nd to child
                child->insertKeyIntoNode(nd->getPair(idxToTraverse));
                nd->removeKey(idxToTraverse);
                //move key from left sibling into child
                child->insertKeyIntoNode(leftSibling->getPair(leftSibling->getNumKeys() - 1));
                leftSibling->removeKey(leftSibling->getNumKeys()-1);
                //move child ptr from lef-t sibling into child
                child->InsertChildAtIndex(leftSibling->getChild(leftSibling->getNumChilds()-1),0);
                leftSibling->removeChild(leftSibling->getNumChilds()-1);
            } else if ((nd->getChild(idxToTraverse+1) != nullptr)
                       && (nd->getChild(idxToTraverse+1)->getNumKeys() >= degree)){
                node<T>* rightSibling = nd->getChild(idxToTraverse+1)   ;
                //move key at idxToTraverse in nd to child
                child->insertKeyIntoNode(nd->getPair(idxToTraverse));
                nd->removeKey(idxToTraverse);
                //move key from right sibling into child
                child->insertKeyIntoNode(rightSibling->getPair(0));
                rightSibling->removeKey(0);
                //move child ptr from right sibling into child
                child->addChildToBack(rightSibling->getChild(0));
                rightSibling->removeChild(0);
            } else {
                /*child and its siblings all have t-1 keys
                 *we merge child w/ one of its siblings
                 *this "involves" moving a key from x into the merged node as new median */
                if (nd->getChild(idxToTraverse-1) != nullptr) {
                    node<T>* leftSibling = nd->getChild(idxToTraverse-1);
                    //merge child w/ left:
                    //move key in nd between left and child ptrs to back of left as new median
                    //passing by reference so we need to do the thing here!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                    std::pair<unsigned int, T> tempPair = nd->getPair(idxToTraverse-1);
                    leftSibling->addKeyToBack(tempPair);
                    nd->removeKey(idxToTraverse-1);
                    //move all keys and children in child to left
                    int childNumPtrs = child->getNumChilds();
                    int childNumKeys = child->getNumKeys();
                    for (int i=0; i < childNumPtrs;i++) {
                        leftSibling->addChildToBack(child->getChild(i));
                    }
                    for (int i=0; i < childNumKeys; i++) {
                        tempPair = child->getPair(i);
                        leftSibling->addKeyToBack(tempPair);
                    }
                    //delete child node and remove ptr to child from nd
                   delete child;
                    nd->removeChild(idxToTraverse);
                } else if (nd->getChild(idxToTraverse+1) != nullptr){
                    node<T>* rightSibling = nd->getChild(idxToTraverse+1);
                    //merge child w/ right:
                    //move key in nd between child and right ptrs to front of right as new median
                    rightSibling->insertKeyIntoNode(nd->getPair(idxToTraverse));
                    nd->removeKey(idxToTraverse);
                    //move all keys and children in child to front of right
                    int childNumPtrs = child->getNumChilds();
                    int childNumKeys = child->getNumKeys();
                    for (int i=0; i < childNumPtrs; i++){
                        rightSibling->InsertChildAtIndex(child->getChild(childNumPtrs-1-i),0);
                    }
                    for (int i=0; i < childNumKeys; i++){
                        rightSibling->insertKeyAtIndex(child->getPair(childNumKeys-1-i),0);
                    }
                    //delete child node and remove ptr to child from nd
                    delete child;
                    nd->removeChild(idxToTraverse);
                }
                if(nd == root && nd->getNumKeys() == 0) {
                    //nd is the root and has no keys, we make its child the new root
                    root = root->getChild(0);
                    delete root->getParent();
                    root->setParent(nullptr);
                }
                deleteKey(keyVal,nd->getNodeToTraverse(keyVal));
            }
        }
    }
}

template <class T>
void btree<T>::insert(std::pair<unsigned int,T> &pear)
{
    if (root==nullptr) {
        node<T> *nd = new node<T>(degree,pear);
        root = nd;
        if (BUMBLEBEE) {
            std::cout << "in insert, we are creating a root\n";
            std::cout << "  root node: " << nd->getNumKeys() << " keys, " <<
                         nd->getNumChilds() << " childs\n";
        }
    } else {
        node<T>* itr = root;
        unsigned int idx = itr->getIndexToInsert(pear.first);
        while (!itr->isLeaf()){
            itr = itr->getChild(idx);
            idx = itr->getIndexToInsert(pear.first);
        }
        if (idx == itr->getNumKeys()) {//if idx > rest of node, just push it to the back of the vector
            itr->addKeyToBack(pear);
        } else {
            itr->insertKeyAtIndex(pear,idx);//insert key in the correct position
        }
        if (itr->getNumKeys() > itr->getMaxKeys()) {//if too many keys in node, split
            if (BUMBLEBEE) {
                std::cout << "in insert, we are not creating a root\n";
                std::cout << "  in node: " << itr->getNumKeys() << " keys, " <<
                             itr->getNumChilds() << " childs\n";
            }
            split(itr);
        }
    }
}

template <class T>
void btree<T>::split(node<T>* current)//current becomes left node!
{
    if (BUMBLEBEE) {
        std::cout << "in split (begin), current has " << current->getNumKeys() <<
                     " keys, " << current->getNumChilds() << " childs\n";
    }
    node<T>* right = new node<T>(degree);//make right node
    right->setParent(current->getParent());//set right parent
    int median = (current->getNumKeys() - 1) / 2;
    std::pair<unsigned int,T> medianKey = current->getPair(median);
    unsigned int j = median + 1;
    for (; j< current->getNumKeys(); j++) {//add right keys and children from current to right node
        std::pair<unsigned int,T> sp = current->getPair(j);
        right->addKeyToBack(sp);
        if (current->getNumChilds()>0) { //if there are children, add them
            right->addChildToBack(current->getChild(j));
        }
    }
    if (current->getNumChilds()>0) { //if there are children, add last child
        right->addChildToBack(current->getChild(j));
    }
    //int toRemove = current->keys.size() / 2 + 1;//how many keys to remove from current
    unsigned int k = current->getNumKeys() - 1;
    for (; k>=median; k--) {
        if (BUMBLEBEE) {
            std::cout << "popped index " << k << ": " << current->getPair(k).second << "\n";
        }
        current->removeKey(k);
        if (right->getNumChilds()>0) { //if there are children, remove them
            current->removeChild(k);
        }
    } //do not need to remove last child here
    if (BUMBLEBEE) {
        std::cout << "in split, current has " << current->getNumKeys() << " keys, " <<
                     current->getNumChilds() << " childs\n";
    }
    /*for (int i=0; i < toRemove; i++){//remove keys and children from current
        current->keys.pop_back();
        current->childs.pop_back();
    }//do not need to remove last child here*/

    /*std::cout << "in split, current has " << current->keys.size() << " keys\n";
    std::cout << "in split, current has " << current->childs.size() << " childs\n";

    std::cout << "in split, right has " << right->keys.size() << " keys\n";
    std::cout << "in split, right has " << right->childs.size() << " childs\n";*/

    if (current == root) {//if we're at the root, we have to make a new node and split into that
	    if (current->getParent() != nullptr) printf("Root's parent is not nullptr!\n");
        //current->parent = new node<T>(degree,medianKey);//make new root
        //current->parent->addChild(current);//add current child (i.e. left)
        //current->parent->addChild(right);//add right child
        node<T> *nr=new node<T>(degree,medianKey);
        root=nr;
        root->addChildToBack(current);
        root->addChildToBack(right);
        //removed set leaf, node isLeaf() function checks this for us
        /*node<T> *lft = root->getChild(0); //replaces: node<T>* lft=root->childs[0];
        if (BUMBLEBEE) {
            std::cout << "   left now has: ";
            for (unsigned int m=0; m<lft->getNumKeys(); m++) {
                std::cout << lft->getPair(m).second << " ";
            }
            std::cout << "\n";
        }
        node<T>* rght=root->getChild(1);
        if (BUMBLEBEE) std::cout << "   right now has: ";
        for (unsigned int m=0; m<rght->getNumKeys(); m++) {
           if (BUMBLEBEE) std::cout << rght->getPair(m).second << " ";
        }
        if (BUMBLEBEE) std::cout << "\n";*/
		//set roots for left and right
		current->setParent(root);
		right->setParent(root);

    } else {
        //current->parent->setLeaf(false);
        unsigned int idxToInsert = current->getParent()->getIndexToInsert(medianKey.first);//get index to insert key in parent
        current->getParent()->insertKeyAtIndex(medianKey,idxToInsert);//insert key into parent
        //child ptr to the left of the new key is the same as before so we don't need to do anything there

        //insert right ptr into correct position in parent (idxToInsert + 1)
        current->getParent()->InsertChildAtIndex(right,idxToInsert + 1); //insert child in parent
        //if the parent is full, we split the parent
        if (current->getParent()->getNumKeys() > current->getParent()->getMaxKeys()) {
            split(current->getParent());
        }
    }
}

template <class T>
void btree<T>::breadthFirst()
{
    if (root==nullptr) return;
    //unsigned int level=0;
    std::queue<node<T>*> qu; //create queue & push root
    qu.push(root);
    std::cout << "| ";
    while (!qu.empty()) { //print items at front of queue & push root
        node<T> *nd = qu.front();
        unsigned int i=0;
        for (; i<nd->getNumKeys(); i++) {
            std::cout << nd->getPair(i).second << " ";
        }
        std::cout << "| ";
        qu.pop();
        for (i=0; i<nd->getNumChilds(); i++) {
            if (nd->getChild(i) != nullptr) {
                qu.push(nd->getChild(i));
            }
        }
    }
    std::cout << "\n";
}

template <class T>
void btree<T>::breadthFirstLevel(int level)
{
    if (root==nullptr) return;
    int lvl=0;
    std::queue<std::pair<node<T>*,int> > qu; //create queue
    std::pair<node<T>*,int> sp;
    sp.first = root;
    sp.second = lvl;
    qu.push(sp); //push root & level
    std::cout << level << ": | ";
    while (!qu.empty()) { //print items at front of queue
        std::pair<node<T>*,int> sp = qu.front();
        unsigned int i=0; //iterator
        if (sp.second==level) { //only print if levels match
            for (; i<sp.first->getNumKeys(); i++) {
                std::cout << sp.first->getPair(i).second << " ";
            }
            std::cout << "| ";
        }
        qu.pop();
        lvl++;
        for (i=0; i<sp.first->getNumChilds(); i++) {
            std::pair<node<T>*,int> cp;
            cp.first = sp.first->getChild(i);
            cp.second = lvl;
            qu.push(cp); //push child node & level
        }
    }
    std::cout << "\n";
}

template <class T>
void btree<T>::breadthFirstLevels()
{
    int n = getNumLevels();
    for (int i=0; i<n; i++) {
        breadthFirstLevel(i);
    }
}

template <class T>
void btree<T>::inOrder()
{
    if (root!=nullptr) {
        inOrder(root);
        std::cout << "\n";
    }
}

template <class T>
void btree<T>::inOrder(node<T>* nd)
{
    if (nd==nullptr) {
        if (BUMBLEBEE) {
            std::cout << "in inorder, nullptr found in child node\n";
        }
        return;
    }
    bool leaf = nd->isLeaf();
    unsigned int i=0;
    for (; i<nd->getNumKeys(); i++) { //print data values in node
        if (!leaf) inOrder(nd->getChild(i)); //run in order on child pointer if not leaf
        std::cout << nd->getPair(i).second << " "; //print data value
    }
    if (!leaf) inOrder(nd->getChild(i)); //in order on last child pointer if not leaf
}

template <class T>
std::pair<bool,T> btree<T>::search(unsigned int keyValue)
{
    if (root!=nullptr) {
        return search(root, keyValue);
    } else {
        return std::make_pair<bool,T>(false,T()); //return false & default T if no root
    }
}

template <class T>
std::pair<bool,T> btree<T>::search(node<T>* nd, unsigned int keyValue)
{
    if (nd==nullptr) {
        return std::make_pair<bool,T>(false, T());
    }
    unsigned int idx = nd->getIndexToInsert(keyValue); //get closest index to key value
    if (idx <= nd->getNumKeys()) { //check size so no seg fault
        if (keyValue == nd->getKeyVal(idx)) { //return pair if key matches
            std::pair<bool,T> pear;
            pear.first = true;
            pear.second = nd->getPair(idx).second;
            return pear;
        } else { //traverse down appropriate node
            return search(nd->getChild(idx), keyValue);
        }
    } else { // idx > nd->getNumKeys
        if (BUMBLEBEE) {
            std::cout << "in search, getindex stepped out of bounds\n";
        }
        return std::make_pair<bool,T>(false,T());
    }
}

template <class T>
void btree<T>::readIn(std::string textfile)
{
    std::ifstream inputfile(textfile); //read file
    std::pair<unsigned int,std::string> sp; //variable to insert into tree

    if (inputfile.is_open()) {
        //while(inputfile.good()) {
        while (inputfile >> sp.first >> sp.second) {
            //std::getline(inputfile,line); //put line into variable
            //inputfile >> sp.first >> sp.second; //set standard pair variables
            insert(sp); //add standard pair to btree
        }
    }
}

//in order print: <key> <data value>
template <class T>
void btree<T>::writeFile(std::string textfile)
{
    if (root!=nullptr) {
        writeFile(root, textfile, true);
    }
}

template <class T>
void btree<T>::writeFile(node<T>* nd, std::string textfile, bool overwrite)
{
    if (nd==nullptr) {
        return;
    }
    bool leaf = nd->isLeaf();
    unsigned int i=0;
    std::ofstream outfile; //file to write to
    if (overwrite) {
        outfile.open(textfile, std::ios::out); //overwrite the file
    }
    outfile.close();
    outfile.open(textfile, std::ios::app); //append to end of file
    for (; i<nd->getNumKeys(); i++) { //print data values in node
        if (!leaf) {
            writeFile(nd->getChild(i), textfile, false); //run in order on child pointer if not leaf
        }
        outfile << nd->getPair(i).first << " " << nd->getPair(i).second << std::endl;
    }
    if (!leaf) {
        writeFile(nd->getChild(i), textfile, false); //in order on last child pointer if not leaf
    }
    outfile.close();
}
