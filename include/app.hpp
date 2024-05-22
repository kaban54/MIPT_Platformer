#ifndef JIJA_APP_HPP
#define JIJA_APP_HPP

#include <iostream>
#include <fstream>
#include "event.hpp"
#include "graphics.hpp"
#include "object_man.hpp"
#include "physics.hpp"
#include "gui.hpp"

class AppController;

class App {
    public:

    explicit App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_);


    void onClock(double dt);
    void handleLevel(double dt);

    void handleGui(double dt);

    void loadPlugins(const std::string& filename);

    void loadLevel(const std::string& filename);

    private:

    Vec2 size;
    EventManager& event_man;
    Gui pause_menu;
    Level lvl;
    ObjectManager obj_man;
    PhysicsModule physics;
    SpriteManager sprite_man;
    GraphicsModule graphics;
    sf::RenderWindow& sfwindow;
    Gui& active_gui;
    bool level_active;

    friend AppController;
};

class AppController {
    public:

    explicit AppController(App& app);

        void onLevelKey(KeyboardContext context);
    
        void   pause();
        void unpause();
        void    exit();

    private:
    App& app;
};

#endif