#ifndef JIJA_OBJMAN_HPP
#define JIJA_OBJMAN_HPP

#include <string>
#include <unordered_map>
#include <vector>

#ifdef WIND
#include <windows.h>

#define ExportFunc  extern "C" __declspec( dllexport )
#else
#define ExportFunc  extern "C"
#include <dlfcn.h>
#endif

#include "drawable.hpp"

typedef Drawable* (*create_obj_func_t)();

struct ObjInfo {
    std::string name;
    std::string texture_file_name;
    create_obj_func_t create_obj_f;

    explicit ObjInfo() = default;

    explicit ObjInfo(const std::string name_,
                     const std::string texture_file_name_,
                     create_obj_func_t create_obj_f_):
        name (name_),
        texture_file_name (texture_file_name_),
        create_obj_f (create_obj_f_) {}
};

typedef ObjInfo (*getObjInfo_t)();

class ObjectManager {
    public:

    explicit ObjectManager() = default;

    void addObject(ObjInfo info);

    void loadPlugin(const std::string& filename);

    bool contains(const std::string& name) const;

    ObjInfo getInfo(const std::string& name) const;

    private:
    std::unordered_map<std::string, ObjInfo> obj_info;
};

#endif