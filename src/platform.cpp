#include "../include/load.hpp"
#include "../include/object_man.hpp"
#include "../include/blocks.hpp"
#include "../include/plugin.hpp"

class Platform : public FixedBlock, public Plugin {
    public:
    explicit Platform():
        FixedBlock(SpriteInfo(0, Vec2(0, 0), Vec2(16, 9)), Vec2(0, 0), Vec2(0, 0))
        {}
    
    virtual void load(std::ifstream &stream) override {
        CHECK_DELIM('{')
        setPos(readVec(stream));
        CHECK_DELIM(',')
        setSize(readVec(stream));
        CHECK_DELIM(',')
        uint8_t color = ((uint8_t) readNum(stream)) % 4;
        CHECK_DELIM(',')
        uint8_t sz = ((uint8_t) readNum(stream)) % 2;
        CHECK_DELIM('}')

        SpriteInfo info(0, Vec2(sz * 16, color * 16), Vec2(16 * (1 + sz), 9));
        setSpriteInfo(info);
    }

    virtual void init() override {}
};

Drawable* createObj() {
    return new Platform;
}

extern "C" ObjInfo getObjInfo() {
    return ObjInfo("Platform", "textures/platforms.png", createObj);
}