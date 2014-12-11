#include "project.h"

Project::Project(int n)
{        
    c1 = -1.45140617*pow(10.0, -60.0);
    c2 = 11.0 - c1;
    e = exp(1.0);
    N = n;
    setCordsX();
}

QVector<double> Project::solveWolfram() {
    double L = length/N;
    for (int j = 0; j < N+1; j++ ) {
        cordsY.push_back(calculateWolfram(L*j));
    }
    return cordsY;
}

void Project::setCordsX() {
    double L = length/N;
    for ( int i =0; i < N+1; i++) {
        cordsX.push_back(L*i);
    }
}

double Project::LeftUp(double L) {
    return (1.0/L -7.0/10.0);
}

double Project::RightUp(double L) {
    return (-1.0/L + 7.0/10.0);
}

double Project::LeftDown(double L) {
    return (-1.0/L - 7.0/10.0);
}

double Project::RightDown(double L) {
    return (1.0/L + 7.0/10.0);
}

double Project::calculateWolfram(double x ) {
    return (7.0*pow(e,140)*(20.0*x+77)-450.0*pow(e,(7.0*x/5.0))+450)/(49*pow(e,140));
}

QVector <double> Project::getCordsX() {
    return cordsX;
}

QVector <double> Project::getCordsY() {
    return cordsY;
}

QVector< QVector<double> > Project::getA() {
    return Al;
}

QVector<double> Project::getb() {
    return bl;
}

void Project::generateLinearAandB() {

    for (int i=0; i<N+1; i++) {
        QVector<double> a;
        Al.push_back(a);
    }

    for (int i=0; i<N+1; i++) {
        for (int j=0; j<N+1; j++)
             Al[i].push_back(0.0);
    }

    double L = length/N;

    for (int i=0; i<N; i++) {
        Al[i][i] += LeftUp(L);
        Al[i][i+1] += RightUp(L);
        Al[i+1][i] += LeftDown(L);
        Al[i+1][i+1] += RightDown(L);
    }

   for (int i=0; i<N+1; i++) {
       Al[i][0] *= U0;
   }
   for (int i=0; i<N+1; i++) {
       bl.push_back(0);
   }

   for (int i = 0; i<N; i++) {
       bl[i] += 4.0*L/2.0;
       bl[i+1] += 4.0*L/2.0;
   }

   bl[N] = dU_dx;

   for (int i=0; i<N+1; i++) {
      bl[i] -= Al[i][0];
   }

   bl.pop_front();
   Al.pop_front();
   for (int i=0; i<Al.length(); i++) {
       Al[i].pop_front();
   }

//   qDebug() << A;
//   qDebug() << A.length();
//   qDebug() << b;
//   qDebug() << b.length();
}

void Project::generateSquareAandB() {

    for (int i=0; i<N+1; i++) {
        QVector<double> a;
        As.push_back(a);
    }

    for (int i=0; i<N+1; i++) {
        for (int j=0; j<N+1; j++)
             As[i].push_back(0.0);
    }

    double L = 2*length/(N);

    for (int i=0; i<N-1; i+=2 ) {
       As[i][i] += (7.0/(3.0*L))-(0.7);
       As[i][i+1] += (-8.0/(3.0*L))+(14.0/15.0);
       As[i][i+2] += (1.0/(3.0*L))-(7.0/30.0);
       As[i+1][i] += (-8.0/(3.0*L))-(14.0/15.0);
       As[i+1][i+1] += (16.0/(3.0*L));
       As[i+1][i+2] += (-8.0/(3.0*L))+(14.0/15.0);
       As[i+2][i] += (1.0/(3.0*L))+(7.0/30.0);
       As[i+2][i+1] += (-8.0/(3.0*L))-(14.0/15.0);
       As[i+2][i+2] += (7.0/(3.0*L))+(0.7);
   }

    qDebug() << As;
    for (int i=0; i<N+1; i++) {
        As[i][0] *= U0;
    }
    for (int i=0; i<N+1; i++) {
        bs.push_back(0);
    }

    for ( int i = 0; i < N-1; i+=2) {
        bs[i] += (2.0/3.0)*L;
        bs[i+1] += (8.0/3.0)*L;
        bs[i+2] += (2.0/3.0)*L;
    }

    bs[N] = dU_dx;

    for (int i=0; i<N+1; i++) {
       bs[i] -= As[i][0];
    }

    bs.pop_front();
    As.pop_front();
    for (int i=0; i<As.length(); i++) {
        As[i].pop_front();
    }

}

QVector<double> Project::linearSolve() {
    generateLinearAandB();
    linearSolution = gauss.solveByGauss(Al, bl);
    double a = U0;
    linearSolution.push_front(a);
    return linearSolution;
}

QVector<double> Project::squareSolve() {
    generateSquareAandB();
    squareSolution = gauss.solveByGauss(As, bs);
    double a = U0;
    squareSolution.push_front(a);
    return squareSolution;
}

QVector<double> Project::getLinearSolution() {
    return linearSolution;
}

QVector<double> Project::getSquareSolution() {
    return squareSolution;
}
