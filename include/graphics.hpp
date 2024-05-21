#ifndef JIJA_GRAPHICS_HPP
#define JIJA_GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "level.hpp"

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