#include "../include/load.hpp"
#include "../include/object_man.hpp"
#include "../include/blocks.hpp"
#include "../include/plugin.hpp"

class Ground1 : public FixedBlock, public Plugin {
    public:
    explicit Ground1():
        FixedBlock(SpriteInfo(0, Vec2(0, 0), Vec2(32, 32)), Vec2(0, 0), Vec2(0, 0))
        {}
    
    virtual void init() override {}
};

Drawable* createObj() {
    return new Ground1;
}

ExportFunc ObjInfo getObjInfo() {
    return ObjInfo("Ground1", "textures/ground1.png", createObj);
}