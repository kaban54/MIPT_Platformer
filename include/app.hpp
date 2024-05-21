#ifndef JIJA_APP_HPP
#define JIJA_APP_HPP

#include <iostream>
#include <fstream>
#include "event.hpp"
#include "graphics.hpp"
#include "object_man.hpp"
// #include "physics.hpp"

class App {
    public:

    explicit App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_);

    void onClock(double dt);

    void loadPlugins(const std::string& filename);

    void loadLevel(const std::string& filename);

    private:

    EventManager& event_man;
    ObjectManager obj_man;
    Level lvl;
    // PhysicsModule physics;
    SpriteManager sprite_man;
    GraphicsModule graphics;
    sf::RenderWindow& sfwindow;
};

#endif