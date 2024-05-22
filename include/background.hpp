#ifndef JIJA_BG_HPP
#define JIJA_BG_HPP

#include <stdint.h>
#include "geometry.hpp"

struct Background {
    uint64_t textureID;
    Vec2 size;

    explicit Background() = default;

    explicit Background(const uint64_t textureID_, Vec2 size_):
    textureID(textureID_),
    size(size_)
    {}
};


#endif