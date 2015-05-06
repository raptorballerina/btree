#include <QApplication>
#include "mainwindow.h"
#include "btree.h"
#include <iostream>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    

    btree<std::string> imCoveredInBees(4,false);
    std::pair<unsigned int,std::string> wasp = {5,"five!"};
    imCoveredInBees.insert(wasp);
    std::pair<unsigned int,std::string> hornet = {10,"ten"};
    imCoveredInBees.insert(hornet);
    std::pair<unsigned int,std::string> bumblebee = {7,"se7en"};
    imCoveredInBees.insert(bumblebee);
    imCoveredInBees.inOrder();
    imCoveredInBees.printRoot();

    /*std::pair<unsigned int,std::string> sp;
    sp=imCoveredInBees.search(10);
    if (sp.first) {
        std::cout << sp.second << "\n";
    }*/

    return a.exec();
}
