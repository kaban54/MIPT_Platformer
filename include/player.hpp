#pragma once
#include "vec2.hpp"
#include "event.hpp"
#include "entity.hpp"


const double PLAYER_WALKING_VEL = 500;
const double PLAYER_JUMPING_VEL = 500;


struct Checkpoint {
    Vec2 spawn_point;
    Vec2 spawn_vel;
    int spawn_health;

    Checkpoint(Checkpoint& cp_) = default;

    explicit Checkpoint(Vec2 sp_, Vec2 sv_, int sh_):
    spawn_point(sp_),
    spawn_vel(sv_),
    spawn_health(sh_)
    {}
};

class Player : public Walking {
  public:
    explicit Player(EventManager& event_man, SpriteInfo sp_info,
                    Vec2 pos_, Vec2 size_, Vec2 velocity_, double mass_, int health_):
        Walking(sp_info, pos_, size_, velocity_, mass_, health_, PLAYER_WALKING_VEL, PLAYER_JUMPING_VEL),
        checkpoint(pos_, velocity_, health_)
        {
            event_man.CreateKeyPressHandler(*this, &Player::onKeyPress);
            event_man.CreateKeyReleaseHandler(*this, &Player::onKeyRelease);
        }

    void onKeyPress(KeyboardContext keyContext);
    void onKeyRelease(KeyboardContext keyContext);

    Vec2 getSpawnPoint() { return checkpoint.spawn_point; }
    void setCheckpoint(Checkpoint& checkpoint_) { checkpoint = checkpoint_;}

    void respawn() {
        setPos(checkpoint.spawn_point);
        setVelocity(checkpoint.spawn_vel);
        setHealth(checkpoint.spawn_health);
    }

    virtual void load(std::ifstream &stream) override {};
    virtual void save(std::ofstream &stream) const override {};

    virtual void die() override { respawn(); }

  private:
    Checkpoint checkpoint;
};