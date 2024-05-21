#include "../include/object_man.hpp"


void ObjectManager::addObject(const ObjInfo info) {
    if (obj_info.contains(info.name)) {
        std::cerr << "object \"" << info.name << "\" already exists.\n";
        return;
    }
    obj_info[info.name] = info;
}

void ObjectManager::loadPlugin(const std::string& filename) {
    void *lib = dlopen(filename.c_str(), RTLD_NOW | RTLD_LOCAL);
    if (!lib) {
        std::cerr << "Cannot load plugin " << filename << "\n" << dlerror() << "\n";
        return;
    }
    getObjInfo_t get_obj_info = (getObjInfo_t) dlsym (lib, "getObjInfo");
    if (get_obj_info) {
        addObject(get_obj_info());
    }
}