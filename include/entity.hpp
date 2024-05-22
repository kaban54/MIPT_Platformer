#ifndef JIJA_ENTITY_HPP
#define JIJA_ENTITY_HPP

#include "drawable.hpp"


struct EntityProperties {
    bool walking;
    bool flying;

    explicit EntityProperties() = default;
};

class Entity : public Drawable {
    public:

    explicit Entity(SpriteInfo info, Vec2 pos_, Vec2 size_, Vec2 velocity_,
                    double mass_, int health_,
                    EntityProperties properties_ = EntityProperties()):
        Drawable(info, pos_, size_),
        mass(mass_),
        velocity(velocity_),
        health(health_),
        prop(properties_) {}


    virtual ObjType getType() const override final {return ENTITY;}

    double getMass()   const { return mass; }
    Vec2 getVelocity() const { return velocity; }
    int    getHealth() const { return health; }

    void setMass(double mass_)          { mass = mass_; }
    void setVelocity(Vec2 velocity_)    { velocity = velocity_; }
    void setHealth(int health_)         { health = health_; }

    void addVelocity(Vec2 delta) { velocity += delta; }

    EntityProperties  properties() const { return prop; }
    EntityProperties& properties()       { return prop; }

    virtual void die() = 0;

    private:
    double mass;
    Vec2 velocity;
    int health;
    EntityProperties prop;
};

class Walking : public Entity {
    public:
    enum WalkingDir {
        LEFT = -1,
        STAND = 0,
        RIGHT = 1
    };

    explicit Walking(SpriteInfo sp_info, Vec2 pos_, Vec2 size_, Vec2 velocity_,
                     double mass_, int health_, double walking_vel_, double jumping_vel_):
        Entity(sp_info, pos_, size_, velocity_, mass_, health_),
        walking_vel(walking_vel_),
        jumping_vel(jumping_vel_),
        walking_dir(STAND),
        stand_flag (false),
        jump_flag(false) {
            properties().walking = true;
            properties().flying = false;
        }

    double getWalkingVel()     const { return walking_vel; }
    double getJumpingVel()     const { return jumping_vel; }
    WalkingDir getWalkingDir() const { return walking_dir; }
    bool isJumping()           const { return jump_flag;   }
    bool isStanding()          const { return stand_flag;  }

    void setWalkingVel(double vel)       { walking_vel = vel; }
    void setJumpingVel(double vel)       { jumping_vel = vel; }
    void setWalkingDir(WalkingDir w_dir) { walking_dir = w_dir; }
    void setJumpFlag(bool jflag)         { jump_flag = jflag; }
    void setStandFlag(bool stand_flag_)  { stand_flag = stand_flag_; }

    Vec2 getVecWalkingVel() const {
        return Vec2(walking_vel * (int)walking_dir, 0);
    }
    Vec2 getVecJumpingVel() const {
        return Vec2(0, -jumping_vel);
    }

    private:
    double walking_vel;
    double jumping_vel;

    WalkingDir walking_dir;
    bool stand_flag;
    bool jump_flag;
};


class Flying : public Entity {
    public:

    explicit Flying(SpriteInfo sp_info, Vec2 pos_, Vec2 size_, Vec2 velocity_,
                     double mass_, int health_, double walking_vel_, double jumping_vel_):
        Entity(sp_info, pos_, size_, velocity_, mass_, health_) {
            properties().walking = false;
            properties().flying = true;
        }
};



#endif