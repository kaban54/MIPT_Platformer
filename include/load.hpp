#ifndef JIJA_LOAD_HPP
#define JIJA_LOAD_HPP

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include "DSL.hpp"
#include "geometry.hpp"


void parskip(std::ifstream &stream);

#define CHECK_DELIM(DELIM_SYMB) {               \
    parskip(stream);                            \
    if (stream.get() != DELIM_SYMB) {           \
        MSG("Syntax ERROR");                    \
        abort();                                \
    }                                           \
    parskip(stream);                            \
}


double readNum(std::ifstream& stream);
Vec2   readVec(std::ifstream& stream);
Rect  readRect(std::ifstream& stream);
std::string readString(std::ifstream& stream);



#endif