/* 
 * File:   tsm.hpp
 * Author: FatemiM
 *
 * Created on July 5, 2010, 11:54 AM
 */

#ifndef TNT_H
#include "TNT\tnt.h"
#endif

#ifndef FSTREAM_
#include <fstream>
#endif // FSTREAM_

#ifndef TSM_HPP
#define	TSM_HPP

using namespace TNT;

class tsm {
public:
    tsm(Array2D< double > &, Array2D< double > &, Array2D< double > &,
            Array2D< double > &, Array2D< double > &); // A, B, C, D, x0
    tsm();
    virtual ~tsm();
    void simPlus1(Array2D< double > &, Array2D< double > &, Array2D< double > &);
    int getNumStates() const;
    int getNumOutputs() const;
    int getNumInputs() const;
    Array2D <double> getX0() const;
    int setInit(Array2D <double>);
    int guardChecker(Array2D< double > &, Array2D< double > &,
        Array2D< double > &, Array2D< int > &);
    Array2D<int> simulate(Array2D<double> &, Array2D<double>, Array2D<double>,
        std::ofstream &, int);

private:
    int n; // Number of states
    int m; // Number of inputs
    int p; // Number of outputs
    Array2D< double > A;
    Array2D< double > B;
    Array2D< double > C;
    Array2D< double > D;
    Array2D< double > x0;
};

#endif	/* TSM_HPP */

