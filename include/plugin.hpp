#ifndef JIJA_PLUGIN_HPP
#define JIJA_PLUGIN_HPP

#include "event.hpp"
#include "player.hpp"
#include "blocks.hpp"
#include "entity.hpp"

class LevelAPI {
    public:
    virtual Player& getPlayer() = 0;
    virtual EventManager& getEventManager() = 0;
    virtual std::vector<Block*>& getBlocks() = 0;
    virtual std::vector<Entity*>& getEntities() = 0;
    virtual void addObj(Drawable* obj) = 0;
};

class Plugin {
    public:

    explicit Plugin() = default;

    void setLvl(LevelAPI* lvl_) {
        lvl_api = lvl_;
        init();
    }

    virtual void init() = 0;

    protected:
    LevelAPI* lvl_api;
};

#endif