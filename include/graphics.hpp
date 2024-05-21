#ifndef JIJA_GRAPHICS_HPP
#define JIJA_GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "level.hpp"


class SpriteManager {
    public:

    explicit SpriteManager() = default;

    void loadTexture(uint64_t id, const std::string& filename);

    void reset();

    void setScreenSize(unsigned int screen_w_, unsigned int screen_h_);

    sf::Sprite getSprite(const Drawable& obj, const Camera& cam);

    sf::Sprite getSprite(const Rect& rect, const SpriteInfo& sprite_info);

    size_t getSize() const;

    private:
    std::unordered_map<uint64_t, sf::Texture> textures;
    unsigned int screen_w;
    unsigned int screen_h;
};

class GraphicsModule {
    public:

    explicit GraphicsModule(unsigned int w, unsigned int h, SpriteManager& sprite_man);

    void drawLevel(const Level& lvl);

    void display();

    void sfDisplay(sf::RenderWindow& window) const;

    private:

    sf::RenderTexture screen;
    SpriteManager& sprite_man;
};


#endif