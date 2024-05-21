#ifndef JIJA_OBJMAN_HPP
#define JIJA_OBJMAN_HPP

#include <dlfcn.h>
#include <string>
#include <unordered_map>
#include <vector>
#include "objbase.hpp"

typedef ObjBase* (*create_obj_func_t)();

typedef ObjInfo (*getObjInfo_t)();

struct ObjInfo {
    std::string name;
    std::string texture_file_name;
    create_obj_func_t create_obj_f;
};

class ObjectManager {
    public:

    explicit ObjectManager() = default;

    void addObject(const ObjInfo info);

    void loadPlugin(const std::string& filename);

    private:
    std::unordered_map<std::string, ObjInfo> obj_info;
};

#endif