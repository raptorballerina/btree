#-------------------------------------------------
#
# Project created by QtCreator 2015-04-30T08:17:28
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = btree
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    btree.cpp \
    node.cpp

HEADERS  += mainwindow.h \
    btree.h \
    node.h

FORMS    += mainwindow.ui
QMAKE_CXXFLAGS += -std=c++11
