#ifndef JIJA_OBJBASE_HPP
#define JIJA_OBJBASE_HPP

#include <iostream>
#include <string>
#include "geometry.hpp"


class ObjBase {
    public:

    virtual ~ObjBase() = default;

    virtual void load(std::ifstream &stream) = 0;
    virtual void save(std::ofstream &stream) = 0;

    // const std::string& getName() const { return name; }

    // const std::string name;
};




#endif