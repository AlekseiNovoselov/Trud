#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <stdio.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);    
    Project* p = new Project(20);
    QVector<double> ls = p->linearSolve();
    QVector<double> ws = p->solveWolfram();
    QVector<double> cx = p->getCordsX();
    qDebug() << "Погрешность";
    for (int i = 0; i < cx.length(); i++) {
        //qDebug() << abs(ls[i] - ws[i]);
        qDebug() << cx[i] << ls[i] << ws[i];
        printf("%20.1f %20.3f %20.3f %20.3f",cx[i], ls[i], ws[i], (ls[i]-ws[i]));
        cout << ls[i] - ws[i] << endl;
    }
    qDebug() << "p Ok";
    // создаем график и добавляем данные:
    ui->widget->addGraph();
    ui->widget->graph(0)->setData(cx, ls);
    // задаем имена осей координат
    ui->widget->xAxis->setLabel("x");
    ui->widget->yAxis->setLabel("y");
    // задаем размеры осей
    ui->widget->xAxis->setRange(p->xBegin, p->xEnd);
    ui->widget->yAxis->setRange(p->yBegin, p->yEnd);
    ui->widget->replot();
    //p->generateAandB();
}

MainWindow::~MainWindow()
{
    delete ui;
}
