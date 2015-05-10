#include <QApplication>
#include "mainwindow.h"
#include "btree.h"
#include <iostream>
#include <stdlib.h> //for rand()

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
/*
    btree<std::string> imCoveredInBees(3);
    std::pair<unsigned int,std::string> wasp = {5,"five"};
    imCoveredInBees.insert(wasp);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> hornet = {10,"ten"};
    imCoveredInBees.insert(hornet);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> bumblebee = {7,"se7en"};
    imCoveredInBees.insert(bumblebee);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> honeybee = {3,"three"};
    imCoveredInBees.insert(honeybee);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> bee = {11,"eleven"};
    imCoveredInBees.insert(bee);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> notBee = {2, "two"};
    imCoveredInBees.insert(notBee);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> woodBee = {13,"thirteen"};
    imCoveredInBees.insert(woodBee);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> queenBee = {9, "nine"};
    imCoveredInBees.insert(queenBee);
    imCoveredInBees.breadthFirstLevels();
    std::pair<unsigned int,std::string> workerBee = {6, "six"};
    imCoveredInBees.insert(workerBee);
    imCoveredInBees.breadthFirstLevels();
    imCoveredInBees.deleteKey(9);
    imCoveredInBees.breadthFirstLevels();
*/
    btree<int> iAmNoLongerCoveredInBees(3);
    std::vector< std::pair<unsigned int,int> > vect;
    for (int i=0; i < 40; i++) {
        int num = rand() % 200;//generate random number between 1 and 50
        std::pair<unsigned int, int> definitelyNotABee = {num,num};
        vect.push_back(definitelyNotABee);
        //add each pair to a vector
        std::cout << "Inserting " << num << std::endl;
        iAmNoLongerCoveredInBees.insert(definitelyNotABee);
        iAmNoLongerCoveredInBees.breadthFirstLevels();
        iAmNoLongerCoveredInBees.inOrder();
    }
    //iAmNoLongerCoveredInBees.inOrder();
    /*std::random_shuffle(vect.begin(),vect.end());
    while (!vect.empty()){
        std::cout << "Deleting" << vect[vect.size()-1].first << std::endl;
        iAmNoLongerCoveredInBees.deleteKey(vect[0].first);
        iAmNoLongerCoveredInBees.breadthFirstLevels();
        std::cout << "\n";
        vect.pop_back();

    }*/
    //go through vector of pairs and delete each one, printing breadthFirstLevels after each deletion

    //test by inserting random numbers between 1 and 50, then deleting some of them

/*    imCoveredInBees.breadthFirst();

	std::cout << "in order print: \n";
    imCoveredInBees.inOrder();
    std::cout << "breadth first print: \n";
    imCoveredInBees.breadthFirstLevels();

    unsigned int k=10;
    std::pair<unsigned int,std::string> sp;
    sp=imCoveredInBees.search(k);
    if (k==sp.first) {
        std::cout << "key " << sp.first << " found with value " << sp.second << "\n";
    }
    
    //create new btree from file
    std::cout << "\nbtree from readin:\n";
    btree<std::string> beetree(3);
    beetree.readIn("./in.txt");
    std::cout << "in order print:\n";
    beetree.inOrder();
    std::cout << "breadth first print:\n";
    beetree.breadthFirstLevels();

    std::cout << "printing file to out.txt\n";
    beetree.writeFile("./out.txt");
*/
    return a.exec();
    //return 0;
}
