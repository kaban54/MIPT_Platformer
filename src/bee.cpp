#include "../include/load.hpp"
#include "../include/object_man.hpp"
#include "../include/entity.hpp"
#include "../include/plugin.hpp"

#include <iostream>

const double BASE_VEL = 200;
const double ROT_VEL = 2;

class Bee : public Flying, public Plugin {
    public:
    explicit Bee():
        Flying(SpriteInfo(0, Vec2(0, 0), Vec2(18, 13)), Vec2(0, 0), Vec2(0, 0), Vec2(0, 0), 0, 0),
        clock(0),
        frame_x(rand() % 4)
        {}
    
    virtual void init() override {
        Vec2 vel(BASE_VEL, 0); 
        vel.Rotate(GetRandAngle());
        setVelocity(vel);

        lvl_api -> getEventManager().CreateClockHandler(*this, &Bee::onClock);
    }

    void onClock(double dt) {
        clock += dt;
        if (clock >= 0.05) {
            clock -= 0.05;
            frame_x = (frame_x + 1) % 4;
        }
        if (Intersect(lvl_api -> getPlayer().getRect(), getRect())) {
            lvl_api -> getPlayer().die();
        }
        Vec2 player_pos = lvl_api -> getPlayer().getPos();
        Vec2 dir = player_pos - getPos();
        Vec2 newvel = getVelocity();

        double angle_dif = dir.GetAngle() - getVelocity().GetAngle();
        if ((angle_dif > 0 && angle_dif < M_PI) || angle_dif < -M_PI) {
            newvel.Rotate(ROT_VEL * dt);
        }
        else newvel.Rotate(-ROT_VEL * dt);
        setVelocity(newvel);
        uint8_t frame_y = 0;
        if (newvel.x < 0) frame_y = 1;

        setFrame(Vec2(frame_x, frame_y));
    }

    private:
    double clock;
    uint8_t frame_x;
};

Drawable* createObj() {
    return new Bee;
}

ExportFunc ObjInfo getObjInfo() {
    return ObjInfo("Bee", "textures/Bee.png", createObj);
}