#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QHBoxLayout>
#include <QStackedLayout>
#include <QString>
#include <QVector>
#include <QMessageBox>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
#include <QUrl>
#include <QDesktopServices>


#include "btree.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:
    void insertSlot();
    void readSlot();
    void writeSlot();
    void openfileSlot();
    void searchSlot();
    void deleteSlot();

public:
    explicit MainWindow(QWidget *parent = 0);
    void plantTree();
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QWidget *mainWidget;

    QVBoxLayout *mainLayout;
    QVBoxLayout *treeLayout;

    std::vector<std::vector<int> > levelVector;

    QHBoxLayout *userfunctionLayout;

    QPushButton *insertButton, *searchButton, *deleteButton, *readButton, *writeButton;
    QLineEdit *insertKeyText, *insertDataText, *searchText, *deleteText;

    QGraphicsView *vw;

    btree<std::string> *beetree;

};

#endif // MAINWINDOW_H
