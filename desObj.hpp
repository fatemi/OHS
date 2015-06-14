/* 
 * File:   desObj.hpp
 * Author: FatemiM
 *
 * Created on June 28, 2010, 2:23 PM
 */

#ifndef STRING_
#include "string"
#endif // STRING_

#ifndef DESOBJ_HPP
#define	DESOBJ_HPP

class desObj {
public:
    desObj();
    desObj(std::string, int);
    ~desObj();
    bool operator == (desObj);
    bool operator != (desObj);

    std::string Name;
    int id;
};

#endif	/* DESOBJ_HPP */

