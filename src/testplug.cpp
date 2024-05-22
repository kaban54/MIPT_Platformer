#include "../include/load.hpp"
#include "../include/object_man.hpp"


class TestObj : public Drawable {
    public:
    explicit TestObj():
        Drawable(SpriteInfo(0, Vec2(0, 0), Vec2(32, 32)), Vec2(0, 0), Vec2(0, 0))
        {}

    virtual ObjType getType() const override {return BLOCK;}

    virtual void load(std::ifstream &stream) override {
        CHECK_DELIM('{')
        setPos(readVec(stream));
        CHECK_DELIM(',')
        setSize(readVec(stream));
        CHECK_DELIM('}')
    }

    virtual void save(std::ofstream &stream) const override {};
};

Drawable* createObj() {
    return new TestObj;
}

extern "C" ObjInfo getObjInfo() {
    return ObjInfo("TestObj", "textures/ground1.png", createObj);
}