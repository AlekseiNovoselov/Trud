#ifndef GAUSS_H
#define GAUSS_H

#include <QVector>
#include <math.h>
#include <QDebug>

class Gauss
{
private:
    static QVector < QVector <double> > pasteTogether(QVector < QVector <double> >, QVector <double>);
public:
    Gauss();
    static QVector <double> solveByGauss(QVector < QVector <double> >, QVector <double>);
};

#endif // GAUSS_H
