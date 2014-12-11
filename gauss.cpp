#include "gauss.h"

Gauss::Gauss()
{

}

QVector < QVector <double> >  Gauss::pasteTogether(QVector < QVector <double> > A, QVector <double> b) {
   for (int i=0; i< b.length(); i++) {
       A[i].push_back(b[i]);
   }
   qDebug() << A;
   return A;
}

QVector <double> Gauss::solveByGauss(QVector < QVector <double> > A, QVector <double> b) {
    QVector <double> x;
    for ( int i = 0; i < A.length(); i++) {
        x.push_back(0.0);
    }

    QVector < QVector <double> > Ab = pasteTogether(A, b);

    int n = Ab.length();
    for (int i=0; i<n; i++) {
        // Search for maximum in this column
        double maxEl = abs(Ab[i][i]);
        int maxRow = i;
        for(int k=i+1; k<n; k++) {
            if (abs(Ab[k][i]) > maxEl) {
                maxEl = abs(Ab[k][i]);
                maxRow = k;
            }
        }
        // Swap maximum row with current row (column by column)
        for (int k=i; k<n+1; k++) {
            double tmp = Ab[maxRow][k];
            Ab[maxRow][k] = Ab[i][k];
            Ab[i][k] = tmp;
        }
        // Make all rows below this one 0 in current column
        for (int k=i+1; k<n; k++) {
            double c = -Ab[k][i]/Ab[i][i];
            for(int j=i; j<n+1; j++) {
                if (i==j) {
                    Ab[k][j] = 0;
                } else {
                    Ab[k][j] += c * Ab[i][j];
                }
            }
        }
     }
        // Solve equation Ax=b for an upper triangular matrix A

     for (int i=n-1; i>-1; i--) {
        x[i] = Ab[i][n]/Ab[i][i];
        for (int k=i-1; k>-1; k--) {
            Ab[k][n] -= Ab[k][i] * x[i];
        }
     }

    return x;
}


