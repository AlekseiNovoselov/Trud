#-------------------------------------------------
#
# Project created by QtCreator 2014-12-09T03:26:38
#
#-------------------------------------------------

QT       += core gui
QT       += printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CustomPlot
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    qcustomplot.cpp \
    project.cpp \
    gauss.cpp

HEADERS  += mainwindow.h \
    qcustomplot.h \
    project.h \
    gauss.h

FORMS    += mainwindow.ui
