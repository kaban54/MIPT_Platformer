#include "../include/load.hpp"
#include "../include/object_man.hpp"
#include "../include/blocks.hpp"
#include "../include/plugin.hpp"

class MovingPlatform : public Block, public Plugin {
    public:
    explicit MovingPlatform():
        Block(SpriteInfo(0, Vec2(0, 0), Vec2(16, 9)), Vec2(0, 0), Vec2(0, 0))
        {
            properties().fixed = false;
            properties().solid = true;
        }
    
    virtual void load(std::ifstream &stream) override {
        CHECK_DELIM('{')
        p1 = readVec(stream);
        setPos(p1);
        CHECK_DELIM(',')
        p2 = readVec(stream);
        CHECK_DELIM(',')
        setSize(readVec(stream));
        CHECK_DELIM(',')
        period = readNum(stream);
        CHECK_DELIM(',')
        uint8_t color = ((uint8_t) readNum(stream)) % 4;
        CHECK_DELIM(',')
        uint8_t sz = ((uint8_t) readNum(stream)) % 2;
        CHECK_DELIM('}')
        SpriteInfo info(0, Vec2(sz * 16, color * 16), Vec2(16 * (1 + sz), 9));
        setSpriteInfo(info);
        velocity = (p2 - p1) / period * 2;
    }

    virtual void save(std::ofstream &stream) const override {}

    virtual void init() override {
        lvl_api -> getEventManager().CreateClockHandler(*this, &MovingPlatform::movePlatform);
    }

    void movePlatform(double dt) {
        move(velocity * dt);
        clock += dt;
        if (clock >= period) {
            clock -= period;
            velocity *= -1;
            move(velocity * clock * 2);
        }
    }

    private:

    Vec2 p1;
    Vec2 p2;
    Vec2 velocity;
    double clock;
    double period;
};

Drawable* createObj() {
    return new MovingPlatform;
}

extern "C" ObjInfo getObjInfo() {
    return ObjInfo("MovingPlatform", "textures/platforms.png", createObj);
}
