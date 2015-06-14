/* 
 * File:   tsm.cpp
 * Author: FatemiM
 * 
 * Created on July 5, 2010, 11:54 AM
 */

#ifndef TNT_H
#include "TNT/tnt.h"
#endif

#ifndef FSTREAM_
#include <fstream>
#endif // FSTREAM_

#ifndef IOSTREAM_
#include <iostream>
#endif // IOSTREAM_

#ifndef TSM_HPP
#include "tsm.hpp"
#endif

using namespace TNT;
using namespace std;

tsm::tsm() {
}

tsm::tsm(Array2D< double > & a, Array2D< double > & b, Array2D< double > & c,
        Array2D< double > & d, Array2D< double > & x_int) {
    A = a;
    B = b;
    C = c;
    D = d;
    x0 = x_int;
    n = A.dim1();
    m = B.dim2();
    p = C.dim1();
}

tsm::~tsm() {
}

int tsm::getNumStates() const {
    return n;
}

int tsm::getNumInputs() const {
    return m;
}

int tsm::getNumOutputs() const {
    return p;
}

int tsm::setInit(Array2D <double> newX0) {
    if (newX0.dim1() == n && newX0.dim2() == 1) {
        x0 = newX0.copy();
        return 1;
    } else {
        cerr << "\n\nERROR: x0 must be the same size as x.\n";
        return 0;
    }
}

Array2D <double> tsm::getX0() const {
    return x0;
}

void tsm::simPlus1(Array2D< double > & x, Array2D< double > & y,
        Array2D< double > & u) {
    y = C * x + D*u;
    x = A * x + B*u;
}

int tsm::guardChecker(Array2D< double > & x, Array2D< double > & H,
        Array2D< double > & b, Array2D <int> & outIndex) {
    // returns the number of detected guard events, zero for no detection.
    // outIndex (last argument) is a vector of integers coressponding to rows
    // of H, where zero-crossing hase been detected.

    int checker = 0; // # of detected guards
    Array2D< double > tester(n, 1, 0.0);
    tester = H * x - b;

    for (int i = 0; i < n; ++i) {
        if (tester[i][0] < 0) {
            ++checker;
            outIndex[i][0] = 1;
        } else {
            outIndex[i][0] = 0;
        }
    }

    return checker;
}

Array2D<int> tsm::simulate(Array2D<double> & u, Array2D<double> H,
        Array2D<double> b, ofstream & fout, int steps) {
    // This method simulates the object (for the maximum of STEPS time steps),
    // and stops running once reaches a guard, for which it returns its
    // corresponding index (row number in H, starting from zero). It writes the
    // simulation results in the referenced ofstream.
    //
    // It returns a vecotr (Array2D) of zeros if no guard detected.

    int numGuard; // number of guards
    Array2D<double> x(n, 1, 0.0);
    x = x0;
    Array2D<double> y(p, 1, 0.0);

    Array2D<int> gResult(H.dim1(), 1, 0);          // guard indeces for output
    Array2D<int> gResultTest(H.dim1(), 1, 0);      // guard indeces for test
    Array2D<int> gResultTestNew(H.dim1(), 1, 0);   // guard indeces for test

    fout << x[0][0] << " " << x[1][0] << "\n";     // writing x0 into file
    for (int i = 0; i < steps; ++i) {
        simPlus1(x, y, u);                         // obtain the simulation for x_k+1
        fout << x[0][0] << " " << x[1][0] << "\n"; // writing x_k+1 into file

        // checking for guards:
        numGuard = guardChecker(x, H, b, gResultTestNew);
        numGuard = 0;
        for (int j = 0; j < H.dim1(); ++j) {
            // the following IF assures "crossing" in contrast with "staying"
            if (gResultTest[j][0] == 0 && gResultTestNew[j][0] == 1) {
                cout << "time step \"" << i << "\"  "
                        << "guard [" << j + 1 << "]\n";
                gResult[j][0] = 1;
                ++numGuard;
            }
        }
        if (numGuard != 0) {
            return gResult;
        }
        gResultTest = gResultTestNew.copy();
    }
    return gResult;
}
