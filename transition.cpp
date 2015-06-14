/* 
 * File:   transition.cpp
 * Author: FatemiM
 * 
 * Created on June 28, 2010, 2:09 PM
 */

#ifndef TRANSITION_HPP
#include "transition.hpp"
#endif // TRANSITION_HPP

using namespace std;

transition::transition() {
}

transition::transition(desObj sObj, desObj tObj, desObj eObj) {
    source = sObj;
    target = tObj;
    byEvent = eObj;
}

transition::~transition() {
}

bool transition::operator ==(transition param) {
    if ( source == param.source && target == param.target &&
            byEvent == param.byEvent && id == param.id )
        return true;
    else
        return false;
}

bool transition::operator !=(transition param) {
    if ( source==param.source && target==param.target &&
            byEvent==param.byEvent && id==param.id)
        return false;
    else
        return true;
}

desObj transition::getSource() {
    return source;
}

desObj transition::getTarget() {
    return target;
}

desObj transition::getEvent() {
    return byEvent;
}

int transition::getID() {
    return id;
}

int transition::setTransition(desObj newSource, desObj newTarget, desObj newEvent) {
    source = newSource;
    target = newTarget;
    byEvent = newEvent;
    return 1;
}

int transition::setID(int newID) {
    id = newID;
    return 1;
}
