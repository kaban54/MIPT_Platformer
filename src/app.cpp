#include "../include/app.hpp"

App::App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_):
    event_man(event_man_),
    lvl(event_man_),
    // physics(),
    sprite_man(),
    graphics(w, h, sprite_man),
    sfwindow(sfwindow_) {
        event_man.CreateClockHandler(*this, &App::onClock);
    }

void App::onClock(double dt) {
    // physics.HandlePhysics(lvl, dt);
    graphics.drawLevel(lvl);
    graphics.sfDisplay(sfwindow);
}

void App::loadPlugins(const std::string& filename) {
    std::fstream file;
    file.open(filename);
    if (!file.is_open()) return;

    std::string plugin_name;
    std::string full_name;
    
    while (std::getline(file, plugin_name)) {
        full_name.assign("plugins/");
        full_name += plugin_name;
        obj_man.loadPlugin(full_name);
    }
}

void App::loadLevel(const std::string& filename) {
    lvl.load(filename, obj_man, sprite_man);
}