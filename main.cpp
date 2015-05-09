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
    std::pair<unsigned int,std::string> notBee = {1, "one"};
    imCoveredInBees.insert(notBee);
    imCoveredInBees.breadthFirst();

    std::cout << "\nin order print: ";
    //imCoveredInBees.inOrder();
    //imCoveredInBees.printLevel(0);
    //imCoveredInBees.printLevel(1);
 //   std::cout << "\nbreadth first print\n";
    imCoveredInBees.breadthFirst();

    std::pair<unsigned int,std::string> sp;
 //   sp=imCoveredInBees.search(10);
    if (sp.first) {
        std::cout << sp.second << "\n";
    }

    return a.exec();
    //return 0;
}
