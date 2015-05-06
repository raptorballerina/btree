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
    std::pair<int,std::string> wasp = {5,"five!"};
    imCoveredInBees.insert(wasp);
    std::pair<int,std::string> hornet = {10,"ten"};
    imCoveredInBees.insert(hornet);
    imCoveredInBees.inOrder();

    return a.exec();
}
