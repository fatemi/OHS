/* 
 * File:   DES.cpp
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

using namespace std;

#include "DES.hpp"

int DES::numDES = 0; // number of DES objects in the memory, initialized to zero.

DES::DES() {
    numDES++;
}

DES::DES(const DES& orig) {
}

DES::~DES() {
    numDES--;
}

vector<desObj> DES::getStateSet() {
    return stateSet;
}

vector<desObj> DES::getEventSet() {
    return eventSet;
}

vector<transition> DES::getTranArray() {
    return tranArray;
}

inline void DES::neatLine(char* inbuf) {
    int len = strlen(inbuf);
    for (int i = 0; i < len; ++i) {
        if (inbuf[i] == '\"') {
            inbuf[i] = ' ';
        }
    }
}

int DES::DOTreader(char * fileName) {
    char inbuf[512];
    int lineNum = 0; // line number in the input file

    desObj aSource, aTarget, anEvent;

    // opening the DOT file:
    ifstream source;
    source.open(fileName, ios_base::in);
    if (!source) {
        cerr << "\nError: cannot open input file: " << fileName << endl;
        //return (0);
    }
    source.close();
    source.open(fileName, ios_base::in);

    string tempStr;
    transition tempTran;

    // ignoring the non-transition part
    while (source.good()) {
        source.getline(inbuf, 512);
        lineNum++;
        if (source.peek() == '\"') {
            break;
        }
    }
    stringstream ins;
    while (source.good()) {
        source.getline(inbuf, 512);
        lineNum++;
        tempTran.setID(lineNum);
        neatLine(inbuf);

        ins.str("");
        ins << inbuf;

        // extracting the source state:
        ins >> tempStr;
        if (tempStr == "START") {
            break;
        }
        aSource.Name = tempStr;
        aSource.id = 0;

        bool inSet = false;
        for (int i = 0; i < stateSet.size(); ++i) {
            if (stateSet[i].Name == aSource.Name) {
                inSet = true;
                break;
            }
        }
        if (!inSet)
            stateSet.push_back(aSource);

        // extracting the target state:
        ins >> tempStr;
        ins >> tempStr;
        aTarget.Name = tempStr;
        aTarget.id = 0;

        inSet = false;
        for (int i = 0; i < stateSet.size(); ++i) {
            if (stateSet[i].Name == aTarget.Name) {
                inSet = true;
                break;
            }
        }
        if (!inSet)
            stateSet.push_back(aTarget);

        // extracting the event label:
        ins >> tempStr;
        ins >> tempStr;
        ins >> tempStr;
        anEvent.Name = tempStr;
        anEvent.id = 0;

        inSet = false;
        for (int i = 0; i < eventSet.size(); ++i) {
            if (eventSet[i].Name == anEvent.Name) {
                inSet = true;
                break;
            }
        }
        if (!inSet)
            eventSet.push_back(anEvent);

        tempTran.setTransition(aSource, aTarget, anEvent);
        inSet = false;
        for (int i = 0; i < tranArray.size(); ++i) {
            if (tranArray[i] == tempTran) {
                inSet = true;
                break;
            }
        }
        if (!inSet)
            tranArray.push_back(tempTran);
    }
    return 1;
}

int DES::tran(desObj & source, desObj & event, desObj & target) {
    // This method find a transition corresponding to the given source state and
    // event name. It returns 1 if a transition detected and update the target
    // refrence variable; otherwise, it returns zero.

    bool inSet = false;
    for (int i = 0; i < stateSet.size(); ++i) {
        if (stateSet[i].Name == source.Name) {
            inSet = true;
            break;
        }
    }
    if (!inSet) {
        cerr << "\n\nWARNING: state name does not exist in DES id = " << id << endl;
    } else {
        for (int i = 0; i < tranArray.size(); ++i) {
            if (source.Name == tranArray[i].getSource().Name && event.Name == tranArray[i].getEvent().Name) {
                target = tranArray[i].getTarget();
                return 1;
            }
        }
        return 0;
    }
}

int DES::pTran(desObj & source, desObj & event, desObj & target) {
    // This method find a transition corresponding to the given source state and
    // event name. It returns 1 if a transition detected and update the target
    // refrence variable; otherwise, it returns zero.

    bool inSet = false;
    for (int i = 0; i < stateSet.size(); ++i) {
        if (stateSet[i].Name == target.Name) {
            inSet = true;
            break;
        }
    }
    if (!inSet) {
        cerr << "\n\nWARNING: state name does not exist in DES id = " << id << endl;
    } else {
        for (int i = 0; i < tranArray.size(); ++i) {
            if (target.Name == tranArray[i].getTarget().Name && event.Name == tranArray[i].getEvent().Name) {
                source = tranArray[i].getSource();
                return 1;
            }
        }
        return 0;
    }
}
