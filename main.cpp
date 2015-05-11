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
    /*btree<int> iAmNoLongerCoveredInBees(3);
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
    }*/

    btree<int> notTheBees(3);
    /*notTheBees.readIn("./in.txt");
    notTheBees.writeFile("./out.txt");
    notTheBees.breadthFirstLevels();
    notTheBees.inOrder();*/

    std::pair<unsigned int,int> sp;
    int n;

    n=185;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=38;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=162;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=5;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=147;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=43;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=185;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=20;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=155;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=73;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=179;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=88;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=162;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=182;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=89;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=19;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=92;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=147;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=46;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=160;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=57;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=120;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=89;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=55;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=125;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=84;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=153;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=137;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=109;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=107;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=184;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=128;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=59;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";
    n=104;	sp.first=n; sp.second=n; notTheBees.insert(sp);	std::cout<<"\ninserted "<<n<<":\n"; notTheBees.breadthFirstLevels(); notTheBees.inOrder(); std::cout<<"\n";

    n=105;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout<<"\ninserted "<<n<<":\n";
    notTheBees.breadthFirstLevels();
    notTheBees.inOrder();
    std::cout<<"\n";

    /*n=124;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=30;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=110;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=156;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=114;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=99;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=67;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=119;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=199;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=194;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=108;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=100;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=51;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=157;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=151;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=108;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=162;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=32;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=64;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=123;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=32;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=143;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=20;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=174;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=166;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    std::cout << "\n";

    n=53;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    notTheBees.breadthFirst();
    notTheBees.inOrder();
    std::cout << "\n";

    n=182;
    sp.first=n;
    sp.second=n;
    notTheBees.insert(sp);
    std::cout << "\ninserted " << n << ":\n";
    notTheBees.breadthFirstLevels();
    notTheBees.breadthFirst();
    notTheBees.inOrder();
    std::cout << "\n";*/

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
