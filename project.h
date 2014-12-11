#ifndef PROJECT_H
#define PROJECT_H

#include <QVector>
#include <math.h>
#include <QDebug>
#include <gauss.h>


class Project
{

public:
    Project(int);

    // настройки графика
    const static int xBegin = 0;
    const static int xEnd = 110;
    const static int yBegin = 0;
    const static int yEnd = 300;


    //параметры программы
    int N; // количество конечных элементов
    const static double length = 100.0; // решение для 0 < x < length
    const static double U0 = 11.0;
    const static double dU_dx = -10.0;
    double c1, c2, e;


    QVector< QVector<double> > Al;
    QVector<double> bl;
    QVector< QVector <double> > As;
    QVector<double> bs;

    QVector<double> linearSolution;
    QVector<double> squareSolution;

    QVector<double> cordsX;
    QVector<double> cordsY;

    double calculateWolfram(double);

    double LeftUp(double L);
    double RightUp(double L);
    double LeftDown(double L);
    double RightDown(double L);

    void generateLinearAandB ();
    void generateSquareAandB ();

    QVector<double> solveWolfram();
    QVector<double> linearSolve();
    QVector<double> squareSolve();

    Gauss gauss;
    void setCordsX();

public:

    QVector <double> getCordsX();
    QVector <double> getCordsY();
    QVector< QVector<double> > getA();
    QVector<double> getb();
    QVector<double> getLinearSolution();
    QVector<double> getSquareSolution();
};

#endif // PROJECT_H
