#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include <iostream>
#include <set>
#include <cstdint>

namespace fmesh {

const static int user_component_type = 1001;

enum component_default_type {
    transform3d_type = 0,
    camera_type,
};

class component
{
public:
    virtual int get_type() const = 0;
    virtual ~component(){}
//    virtual bool event() = 0;
};


}

#endif
