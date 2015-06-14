/* 
 * File:   transition.hpp
 * Author: FatemiM
 *
 * Created on June 28, 2010, 2:09 PM
 */

#ifndef DESOBJ_HPP
#include "desObj.hpp"
#endif


#ifndef TRANSITION_HPP
#define	TRANSITION_HPP

class transition {
public:
    transition();
    transition(desObj, desObj, desObj);
    virtual ~transition();
    bool operator == (transition);
    bool operator != (transition);
    desObj getSource();
    desObj getTarget();
    desObj getEvent();
    int getID();
    int setTransition(desObj, desObj, desObj);
    int setID(int);
    
private:
    desObj source;
    desObj target;
    desObj byEvent;
    int id;
};

#endif	/* TRANSITION_HPP */

