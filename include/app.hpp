#ifndef JIJA_APP_HPP
#define JIJA_APP_HPP

#include <iostream>
#include <fstream>
#include "event.hpp"
#include "graphics.hpp"
#include "object_man.hpp"
#include "physics.hpp"
#include "gui.hpp"

class PauseController {
    public:

    explicit PauseController(EventManager& lvl, EventManager& pause, bool& lvl_active);

        void onLevelKey(KeyboardContext context);
        void onPauseKey(KeyboardContext context);
    
        void   pause();
        void unpause();

    private:
    bool& level_active;
    EventManager& level_ev_man;
    EventManager& pause_ev_man;

};

class App {
    public:

    explicit App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_);


    void onClock(double dt);
    void handleLevel(double dt);

    void handleGui(double dt);

    void loadPlugins(const std::string& filename);

    void loadLevel(const std::string& filename);

    private:

    EventManager& event_man;
    Gui pause_menu;
    Level lvl;
    PauseController pause_ctrl;
    ObjectManager obj_man;
    PhysicsModule physics;
    SpriteManager sprite_man;
    GraphicsModule graphics;
    sf::RenderWindow& sfwindow;
    Gui& active_gui;
    bool level_active;
};

#endif