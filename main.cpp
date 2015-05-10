#include <QApplication>
#include "mainwindow.h"
#include "btree.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    btree<std::string> imCoveredInBees(3);
    std::pair<unsigned int,std::string> wasp = {5,"five"};
    imCoveredInBees.insert(wasp);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> hornet = {10,"ten"};
    imCoveredInBees.insert(hornet);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> bumblebee = {7,"se7en"};
    imCoveredInBees.insert(bumblebee);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> honeybee = {3,"three"};
    imCoveredInBees.insert(honeybee);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> bee = {11,"eleven"};
    imCoveredInBees.insert(bee);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> notBee = {2, "two"};
    imCoveredInBees.insert(notBee);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> woodBee = {13,"thirteen"};
    imCoveredInBees.insert(woodBee);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> queenBee = {9, "nine"};
    imCoveredInBees.insert(queenBee);
    imCoveredInBees.breadthFirst();
    std::pair<unsigned int,std::string> workerBee = {6, "six"};
    imCoveredInBees.insert(workerBee);
    imCoveredInBees.breadthFirst();
    imCoveredInBees.deleteKey(11);
    imCoveredInBees.breadthFirst();

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

    std::cout << "\nand then there was this...\n";
    beetree.writeFile("./out.txt");

    return a.exec();
    //return 0;
}
