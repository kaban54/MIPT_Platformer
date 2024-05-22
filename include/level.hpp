#ifndef JIJA_LEVEL_HPP
#define JIJA_LEVEL_HPP

#include <string>
#include <vector> // myvector)
#include "blocks.hpp"
#include "camera.hpp"
#include "entity.hpp"
#include "event.hpp"
#include "object_man.hpp"
#include "player.hpp"
#include "sprite_man.hpp"
#include "vec2.hpp"


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

    Player& getPlayer();

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

    const std::vector<Entity*>& getEntities() const;
    std::vector<Entity*>& getEntities();

    EventManager& getEventManager();

    void addObj(Drawable* obj);

    void save(const std::string& filename) const;
    void load(const std::string& filename, const ObjectManager& obj_man, SpriteManager& sprite_man);

    private:
    Player* player;
    Background bg;
    Camera cam;
    Vec2 grav_acc;
    Rect bounds;
    Vec2 spawn_point;

    std::vector<Drawable*> drawable;
    std::vector<Block*> blocks;
    std::vector<Entity*> entities;
    
    std::string lvl_name;

    EventManager& event_man;
};



#endif