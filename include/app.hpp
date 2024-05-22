#ifndef JIJA_APP_HPP
#define JIJA_APP_HPP

#include <iostream>
#include <fstream>
#include "event.hpp"
#include "graphics.hpp"
#include "object_man.hpp"
#include "physics.hpp"

class PauseController {
    public:

    explicit PauseController(EventManager& lvl, EventManager& pause);

        void onLevelKey(KeyboardContext context);
        void onPauseKey(KeyboardContext context);
    
        void   pause();
        void unpause();

    private:
    EventManager& level_ev_man;
    EventManager& pause_ev_man;

};

class App {
    public:

    explicit App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_);

    void handleLevel(double dt);

    void loadPlugins(const std::string& filename);

    void loadLevel(const std::string& filename);

    private:

    EventManager& event_man;
    EventManager pause_ev_man;
    Level lvl;
    PauseController pause_ctrl;
    ObjectManager obj_man;
    PhysicsModule physics;
    SpriteManager sprite_man;
    GraphicsModule graphics;
    sf::RenderWindow& sfwindow;
};

#endif