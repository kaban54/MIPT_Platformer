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

void App::loadLevel(const std::string& filename) {
    lvl.load(filename);
}