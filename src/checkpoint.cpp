#include "../include/load.hpp"
#include "../include/object_man.hpp"
#include "../include/blocks.hpp"
#include "../include/plugin.hpp"

class Checkpoint : public FixedBlock, public Plugin {
    public:
    explicit Checkpoint():
        FixedBlock(SpriteInfo(0, Vec2(17, 17), Vec2(14, 47)), Vec2(0, 0), Vec2(0, 0)),
        completed(false)
        {
            properties().solid = false;
        }

    virtual void init() override {
        lvl_api -> getEventManager().CreateClockHandler(*this, &Checkpoint::onClock);
    }

    void onClock(double dt) {
        if (completed) return;
        Player& player = lvl_api -> getPlayer();
        if (Intersect(player.getRect(), getRect())) {
            completed = true;
            player.setCheckpoint(CheckpointInfo(getPos(), Vec2(0, 0), 100));
            SpriteInfo info = getSpriteInfo();
            info.spritePos = Vec2(113, 17);
            setSpriteInfo(info);
        }
    }

    private:
    bool completed;
};

Drawable* createObj() {
    return new Checkpoint;
}

ExportFunc ObjInfo getObjInfo() {
    return ObjInfo("Checkpoint", "textures/staticObjects.png", createObj);
}