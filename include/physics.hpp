#ifndef JIJA_PHYSICS_HPP
#define JIJA_PHYSICS_HPP

#include <algorithm>
#include "level.hpp"

class PhysicsModule {
    public:

    void HandlePhysics(Level& lvl, double dt);

    private:

    void HandleEntities(Level& lvl, double dt);
    void HandleWalking(Walking& ent, Level& lvl, double dt);
    void HandleFlying(Flying& ent, Level& lvl, double dt);

};

bool Intersect(const Entity& ent, const Block& blk);

void Collide(Walking& ent, Block& blk);
void Collide(Flying& ent, Block& blk);

Rect::RectSide PushOut(Block& blk, Entity& ent);

#endif