#include "../include/level.hpp"

Level::Level(EventManager& event_man_):
    bg(),
    cam(),
    grav_acc(Vec2(0, 900)),
    bounds(),
    drawable(),
    lvl_name(),
    event_man(event_man_)
    {
        event_man.CreateClockHandler(cam, &Camera::followTarget);
    }

Level::~Level() {
    for (auto elem : drawable) delete elem;
}

const Camera& Level::getCam() const {
    return cam;
}

Camera& Level::getCam() {
    return cam;
}

const Background& Level::getBackground() const {
    return bg;
}

Background& Level::getBackground() {
    return bg;
}

Vec2 Level::getAcc() const {
    return grav_acc;
}

Rect Level::getBounds() const {
    return bounds;
}

const std::vector<Drawable*>& Level::getDrawable() const {
    return drawable;
}

std::vector<Drawable*>& Level::getDrawable() {
    return drawable;
}

const std::vector<Block*>& Level::getBlocks() const {
    return blocks;
}

std::vector<Block*>& Level::getBlocks() {
    return blocks;
}

const std::vector<Entity*>& Level::getEntities() const {
    return entities;
}

std::vector<Entity*>& Level::getEntities() {
    return entities;
}

EventManager& Level::getEventManager() {
    return event_man;
}
