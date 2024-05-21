#ifndef JIJA_LEVEL_HPP
#define JIJA_LEVEL_HPP

#include <string>
#include <vector> // myvector)
#include "blocks.hpp"
#include "camera.hpp"
// #include "DSL.hpp"
// #include "entity.hpp"
#include "event.hpp"
#include "object_man.hpp"
// #include "player.hpp"
#include "vec2.hpp"
// #include "movingblock.hpp"


struct Background {
    uint64_t textureID;
    Vec2 size;

    explicit Background() = default;

    explicit Background(const uint64_t textureID_, Vec2& size_):
    textureID(textureID_),
    size(size_)
    {}
};

class Level {
    public:

    explicit Level(EventManager& event_man_);

    ~Level();

    const Camera& getCam() const;
    Camera& getCam();

    const Background& getBackground() const;
    Background& getBackground();

    Vec2 getAcc() const;
    Rect getBounds() const;

    const std::vector<Drawable*>& getDrawable() const;
    std::vector<Drawable*>& getDrawable();

    const std::vector<Block*>& getBlocks() const;
    std::vector<Block*>& getBlocks();

    // const std::vector<Entity*>& getEntities() const { return entities; }
    // std::vector<Entity*>& getEntities() { return entities; }

    const std::vector<std::string>& getTextures() const;
    std::vector<std::string>& getTextures();

    EventManager& getEventManager();

    void save(const std::string& filename) const;
    void load(const std::string& filename, const ObjectManager& obj_man, SpriteManager& sprite_man);

    private:
    Background bg;
    Camera cam;
    Vec2 grav_acc;
    Rect bounds;
    Vec2 spawn_point;

    std::vector<Drawable*> drawable;
    std::vector<Block*> blocks;
    // std::vector<Entity*> entities;
    
    std::string lvl_name;

    EventManager& event_man;
};



#endif