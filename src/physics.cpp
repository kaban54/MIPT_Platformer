#include "../include/physics.hpp"


void PhysicsModule::HandlePhysics(Level& lvl, double dt) {
    std::vector<Block*>&  blocks   = lvl.getBlocks();
    std::vector<Entity*>& entities = lvl.getEntities();

    for (auto entity_it = entities.begin(); entity_it != entities.end(); ++entity_it) {
        Entity& ent = **entity_it;
        ent.setStandFlag(false);

        ent.move(ent.getVelocity() * dt);
        Walking* wkg = nullptr;
        if (ent.properties().can_walk_and_jump) {
            wkg = dynamic_cast<Walking*>(*entity_it);
            wkg -> move(wkg -> getVecWalkingVel() * dt);
        }

        for (auto block_it = blocks.begin(); block_it != blocks.end(); ++block_it) {
            Block& blk = **block_it;
            if (Intersect(ent, blk)) Collide(ent, blk);
        }

        if (wkg) {
            if (wkg -> isJumping() && wkg -> isStanding()) {
                wkg -> addVelocity(wkg -> getVecJumpingVel());
            }
        }

        if (!ent.isStanding())  {
            Vec2 grav_acc = lvl.getAcc();
            ent.addVelocity(grav_acc * dt);
        }

        if (!Intersect(ent.getRect(), lvl.getBounds())) ent.die();
    }
}

bool Intersect(const Entity& ent, const Block& blk) {
    return Intersect(ent.getRect(), blk.getRect());
}

void Collide(Entity& ent, Block& blk) {
    Rect::RectSide col_side = PushOut(blk, ent);


    if (col_side == Rect::Left || col_side == Rect::Right) {
        ent.setVelocity(Vec2(0, ent.getVelocity().y));
    }
    else {
        if (col_side == Rect::Top) {
            ent.setStandFlag(true);
        }
        ent.setVelocity(Vec2(ent.getVelocity().x, 0));
    }
}


Rect::RectSide PushOut(Block& blk, Entity& ent) {
    Rect fixed_rect = blk.getRect();
    Rect free_rect  = ent.getRect();

    double xpos = fixed_rect.right() - free_rect.left();
    double xneg = free_rect.right() - fixed_rect.left();
    double ypos = fixed_rect.bot() - free_rect.top();
    double yneg = free_rect.bot() - fixed_rect.top();
    double min = std::min({xpos, xneg, ypos, yneg});
    
    if (min == xpos) {
        ent.move(Vec2(xpos, 0));
        return Rect::Right;
    }
    if (min == xneg) {
        ent.move(Vec2(-xneg, 0));
        return Rect::Left;
    }
    if (min == ypos) {
        ent.move(Vec2(0, ypos));
        return Rect::Bot;
    }
    ent.move(Vec2(0, -yneg));
    return Rect::Top;
}
