#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    mainWidget = new QWidget;
    mainLayout = new QVBoxLayout;
    userfunctionLayout = new QHBoxLayout;

    treeLayout = new QVBoxLayout;

    insertButton = new QPushButton("Insert");
    searchButton = new QPushButton("Search");
    deleteButton = new QPushButton("Delete");
    readButton = new QPushButton("Read from File");
    writeButton = new QPushButton("Write to File");

    insertKeyText = new QLineEdit;
    insertDataText = new QLineEdit;
    searchText = new QLineEdit;
    deleteText = new QLineEdit;

    insertKeyText->setFixedWidth(50);
    insertDataText->setFixedWidth(200);
    searchText->setFixedWidth(50);
    deleteText->setFixedWidth(50);

    userfunctionLayout->addWidget(insertKeyText);
    userfunctionLayout->addWidget(insertDataText);
    userfunctionLayout->addWidget(insertButton);
    userfunctionLayout->addWidget(searchText);
    userfunctionLayout->addWidget(searchButton);
    userfunctionLayout->addWidget(deleteText);
    userfunctionLayout->addWidget(deleteButton);
    userfunctionLayout->addWidget(readButton);
    userfunctionLayout->addWidget(writeButton);

    connect(insertButton, SIGNAL(clicked()), this, SLOT(insertSlot()));
    connect(readButton, SIGNAL(clicked()), this, SLOT(readSlot()));
    connect(writeButton, SIGNAL(clicked()), this, SLOT(writeSlot()));
    connect(searchButton, SIGNAL(clicked()), this, SLOT(searchSlot()));
    connect(deleteButton, SIGNAL(clicked()),this,SLOT(deleteSlot()));
    mainLayout->addLayout(userfunctionLayout);
    mainLayout->addLayout(treeLayout);

    mainWidget->setLayout(mainLayout);

    setCentralWidget(mainWidget);
    setWindowTitle("BTree");

    beetree = new btree<std::string>(3);
}

void MainWindow::plantTree()
{
    if (beetree->getNumLevels()==0) return;

    static std::vector<QLineEdit*> addedNodeBoxes;
    static std::vector<QWidget*> addedWidgets;

    for (int i=0; i < addedNodeBoxes.size(); i++)
        delete addedNodeBoxes[i];
    for (int i=0; i < addedWidgets.size(); i++)
        delete addedWidgets[i];

    addedWidgets.clear();
    addedNodeBoxes.clear();

    for (int k=0; k<beetree->getNumLevels(); k++) {
        levelVector = beetree->getArraysAtLevel(k); //vector of vectors for that level
        QHBoxLayout* tempLayout = new QHBoxLayout;
        for (int i=0; i<levelVector.size(); i++) { //
            QString qs=" ";
            for (int j=0; j<levelVector[i].size(); j++) { //inner loop for each level
                if (qs.length()>1) {
                    qs.append("| ");
                }
                qs.append(QString::number(levelVector[i][j]));
                qs.append(" ");
            }
            QLineEdit* nodeBox = new QLineEdit;
            nodeBox->setText(qs); //rootBox->setText(qs);

            addedNodeBoxes.push_back(nodeBox);
            tempLayout->addWidget(nodeBox);

            QFontMetrics fm(nodeBox->fontMetrics());
            int w = fm.width(nodeBox->text());
            nodeBox->setReadOnly(true);
            nodeBox->setAlignment(Qt::AlignCenter);
            nodeBox->setFixedWidth(w*1.10);
            nodeBox->setFixedHeight(30);
        }
        levelVector.clear();

        QWidget* tempWidget = new QWidget;
        addedWidgets.push_back(tempWidget);
        tempWidget->setLayout(tempLayout);
        treeLayout->addWidget(tempWidget);

    }
}

void MainWindow::deleteSlot(){
    unsigned int toDelete = deleteText->text().toUInt();
    beetree->deleteKey(toDelete);
    plantTree();
    deleteText->clear();
}

void MainWindow::searchSlot() {
    unsigned int query = searchText->text().toUInt();
    std::pair<bool, std::string> retVal = beetree->search(query);
    searchText->clear();
    QMessageBox* box = new QMessageBox;
    if (retVal.first)
        box->setText(QString::fromStdString(retVal.second));
    else
        box->setText("Value not found!");
    box->exec();
}

void MainWindow::insertSlot()
{
    if (insertKeyText->text().trimmed().length()==0) return;
    unsigned int key = insertKeyText->text().toUInt();
    std::string data = insertDataText->text().toStdString();
    std::pair<unsigned int, std::string> pear;
    pear.first = key;
    pear.second = data;
    beetree->insert(pear);
    insertKeyText->clear();
    insertDataText->clear();

    plantTree();
}

void MainWindow::readSlot()
{
    if (beetree->getNumLevels()==0) return;
    beetree->readIn("./in.txt");
    plantTree();
}

void MainWindow::writeSlot()
{
    if (beetree->getNumLevels()==0) return;
    beetree->writeFile("./out.txt");
    QGraphicsScene *scn = new QGraphicsScene();
    QGraphicsView *vw = new QGraphicsView(scn);
    QGraphicsPixmapItem *itm = new QGraphicsPixmapItem(*(new QPixmap(":img/images/trex_write.jpg")));
    vw->setFixedSize(604,280);
    scn->addItem(itm);
    vw->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
