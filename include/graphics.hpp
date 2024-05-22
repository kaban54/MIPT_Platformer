#ifndef JIJA_GRAPHICS_HPP
#define JIJA_GRAPHICS_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "level.hpp"
#include "gui.hpp"

class GraphicsModule {
    public:

    explicit GraphicsModule(unsigned int w, unsigned int h, SpriteManager& sprite_man);

    void setFont(const sf::Font& fnt_);

    void drawLevel(const Level& lvl);

    void drawGui(const Gui& gui);

    void drawWidget(const Widget& wid);

    void drawText(const Text& text);

    void display();

    void sfDisplay(sf::RenderWindow& window) const;

    private:

    sf::RenderTexture screen;
    SpriteManager& sprite_man;
    sf::Font fnt;
};


#endif