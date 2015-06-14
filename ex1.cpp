/* 
 * File:   ex1.cpp
 * Author: FatemiM
 *
 * Created on June 28, 2010, 2:02 PM
 */

#ifndef IOSTREAM_
#include "iostream"
#endif

#ifndef FSTREAM_
#include <fstream>
#endif // FSTREAM_

#ifndef DESOBJ_HPP
#include "desObj.hpp"
#endif // DESOBJ_HPP

#ifndef TRANSITION_HPP
#include "transition.hpp"
#endif // TRANSITION_HPP

#ifndef TNT_H
#include "TNT/tnt.h"
#endif

#ifndef VECTOR_
#include "vector"
#endif

#ifndef TSM_H
#include "tsm.hpp"
#endif

#ifndef STRING_H
#include <string.h>
#endif

#ifndef DES_HPP
#include "DES.hpp"
#endif

#ifndef DESOBJ_HPP
#include "desObj.hpp"
#endif // DESOBJ_HPP

using namespace std;
using namespace TNT;
/*
 * 
 */

string guardName(int);

int main(int argc, char** argv) {

    desObj* aState = new desObj;
    desObj anEvent;

    /*
    aState->Name = "test1";
    aState->id = 1;
    anEvent.Name = "mehdi";
    anEvent.id = 21;

    transition aTran(*aState, *aState, anEvent);

    cout << aTran.getSource().Name << " -> "
            << aTran.getEvent().Name << " -> "
            << aTran.getTarget().Name << endl;

    delete aState; 
    */


    
    // testing TSM:

    Array2D< double > A(2, 2, 0.0); /* create MxN array; all zeros */
    A[0][0] = 1.02;
    A[1][1] = 1.03;

    Array2D< double > B(2, 1, 0.0);
    Array2D< double > C(1, 2, 1.0);
    Array2D< double > D(1, 1, 0.0);
    Array2D< double > x_0(2, 1, 1.0);

    // gurad detector matrices H and b:
    Array2D< double > H(2, 2, 0.0); /* create MxN array; all zeros */
    H[0][0] = 1.0;
    H[1][1] = -1.0;

    Array2D< double > b(2, 1, 0.0); /* create MxN array; all zeros */
    b[0][0] = 0.0;
    b[1][0] = -10.0;

    tsm plant(A, B, C, D, x_0);

    Array2D< double > x(plant.getNumStates(), 1, 0.0);
    x = x_0.copy();

    Array2D< double > y(plant.getNumOutputs(), 1, 0.0);
    Array2D< double > u(plant.getNumInputs(), 1, 0.0);

    ////////////////
    // opening an output file (named as "_test1.txt")
    ////////////////
    char* outputFile1 = new char;
    outputFile1 = "_state_values.txt";
    ofstream fout1;
    fout1.open(outputFile1);
    if (!fout1) {
        cerr << "Error: cannot open output file: " << outputFile1 <<
                " for output\n";
        return 0;
    }
    ////////////////

    int steps = 200; // maximum number of discrete time steps
    Array2D<int> guard(H.dim1(), 1, 0);
    guard = plant.simulate(u, H, b, fout1, steps);
    fout1 << "\n\n\n";
    for (int i = 0; i < H.dim1(); ++i) {
        cout << guard[i][0] << endl;
        //fout1 << guardName(guard[i][0]) << endl;
    }


    fout1.close();

    // testing DES class:

    char* inputFile1 = new char;
    inputFile1 = "c1.dot";
    DES testDES;
    testDES.DOTreader(inputFile1);
    cout << "\n\nDES:\n\n";
    cout << testDES.getStateSet().size() << endl;
    for (int i = 0; i < testDES.getStateSet().size(); ++i) {
        cout << testDES.getStateSet()[i].Name << endl;
    }
    for (int i = 0; i < testDES.getEventSet().size(); ++i) {
        cout << testDES.getEventSet()[i].Name << endl;
    }
    for (int i = 0; i < testDES.getTranArray().size(); ++i) {
        cout << testDES.getTranArray()[i].getSource().Name << " -> "
                << testDES.getTranArray()[i].getEvent().Name << " -> "
                << testDES.getTranArray()[i].getTarget().Name << endl;
    }

    desObj source, event, target;
    source.Name = "[[[s,[alpha,0]],[e]],1]";
    // test 1:
    event.Name = "delta";
    testDES.tran(source, event, target);
    cout << "\n\n\n" << target.Name << endl;
    // test 2:
    event.Name = "tick";
    target.Name = "[[[s,[alpha,2]],[s]],1]";
    testDES.pTran(source, event, target);
    cout << "\n\n\n" << source.Name << endl;

    return 0;
}

string guardName(int name) {
    string str;
    char c[256];
    sprintf(c, "%d", name);
    str = c;
    return str;
}

