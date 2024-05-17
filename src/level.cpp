#include "../include/level.hpp"

Level::Level(EventManager& event_man_):
    bg(),
    cam(),
    grav_acc(Vec2(0, 900)),
    bounds(),
    drawable(),
    blocks(),
    texture_name_table(),
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

// const std::vector<Entity*>& getEntities() const { return entities; }
// std::vector<Entity*>& getEntities() { return entities; }

const std::vector<std::string>& Level::getTextures() const {
    return texture_name_table;
}

std::vector<std::string>& Level::getTextures() {
    return texture_name_table;
}

EventManager& Level::getEventManager() {
    return event_man;
}