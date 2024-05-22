#ifndef JIJA_PHYSICS_HPP
#define JIJA_PHYSICS_HPP

#include <algorithm>
#include "level.hpp"

class PhysicsModule {
    public:

    void HandlePhysics(Level& lvl, double dt);

};

bool Intersect(const Entity& ent, const Block& blk);

void Collide(Entity& ent, Block& blk);

Rect::RectSide PushOut(Block& blk, Entity& ent);

#endif