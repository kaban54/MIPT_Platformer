#ifndef JIJA_OBJBASE_HPP
#define JIJA_OBJBASE_HPP

#include <iostream>
#include <string>
#include "geometry.hpp"

enum ObjType {
    BLOCK,
    ENTITY,
    PROJECTILE,
};

class ObjBase {
    public:

    virtual ~ObjBase() = default;

    virtual ObjType getType() const = 0;

    virtual void load(std::ifstream &stream) = 0;
    virtual void save(std::ofstream &stream) const = 0;

    // const std::string& getName() const { return name; }

    // const std::string name;
};




#endif