/* 
 * File:   desObj.cpp
 * Author: FatemiM
 * 
 * Created on June 28, 2010, 2:23 PM
 */

#ifndef DESOBJ_HPP
#include "desObj.hpp"
#endif // DESOBJ_HPP

#ifndef STRING_
#include "string"
#endif // STRING_

using namespace std;

desObj::desObj() {}

desObj::desObj(string name, int idNum) {
    Name = name;
    id = idNum;
}

desObj::~desObj() {}

bool desObj::operator ==(desObj param) {
    if ( Name==param.Name && id==param.id )
        return true;
    else
        return false;
}

bool desObj::operator !=(desObj param) {
    if ( Name==param.Name && id==param.id )
        return false;
    else
        return true;
}
