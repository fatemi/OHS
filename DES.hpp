/* 
 * File:   DES.hpp
 * Author: FatemiM
 *
 * Created on July 7, 2010, 2:02 PM
 */

#ifndef VECTOR_
#include "vector"
#endif

#ifndef TSM_H
#include "tsm.hpp"
#endif

#ifndef STRING_H
#include <string.h>
#endif

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

#ifndef DES_HPP
#define	DES_HPP

class DES {
public:
    DES();
    DES(const DES& orig);
    virtual ~DES();
    int DOTreader(char *);
    static int numDES; // number of DES exist in the memory

    std::vector<desObj> getStateSet();
    std::vector<desObj> getEventSet();
    std::vector<transition> getTranArray();
    int getID();
    int tran(desObj &, desObj &, desObj &);  // gives the target state in a given transition
    int pTran(desObj &, desObj &, desObj &); // gives the source state in a given transition

private:
    std::vector<transition> tranArray;
    std::vector<desObj> stateSet;
    std::vector<desObj> eventSet;
    desObj initState;
    int id;

    void neatLine(char *);
};

#endif	/* DES_HPP */

