#include "../include/load.hpp"


void parskip(std::ifstream &stream) {
    while (std::isspace(stream.peek())) stream.get();
}

double readNum(std::ifstream& stream) {
    parskip(stream);
    double result = 0;
    stream >> result;

    return result;
}

Vec2 readVec(std::ifstream& stream) {
    CHECK_DELIM('(')
        double x = readNum(stream);
        CHECK_DELIM(',')
        double y = readNum(stream);
    CHECK_DELIM(')')

    return Vec2(x, y);
}

Rect readRect(std::ifstream &stream) {
    CHECK_DELIM('(')
        Vec2 pos = readVec(stream);
        CHECK_DELIM(',')
        Vec2 size = readVec(stream);
    CHECK_DELIM(')')

    return Rect(pos, size);
}

std::string readString(std::ifstream& stream) {
    std::string result;
    
    parskip(stream);
    char c = stream.get(); 
    if (c != '"') {
        MESSAGE("%c, Syntax Error while loading", c);
        abort();
    }

    c = stream.get();
    while (c != '"') {
        result.push_back(c);
        c = stream.get();
    }

    // std::cout << result;

    return result;
}