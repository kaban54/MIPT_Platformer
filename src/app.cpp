#include "../include/app.hpp"

PauseController::PauseController(EventManager& lvl, EventManager& pause):
    level_ev_man (lvl),
    pause_ev_man (pause)
    {
        level_ev_man.CreateKeyPressHandler(*this, &PauseController::onLevelKey);
        pause_ev_man.CreateKeyPressHandler(*this, &PauseController::onPauseKey);
    }


void PauseController::onLevelKey(KeyboardContext context) {
    if (context.key == Key::Tab) pause();
}

void PauseController::onPauseKey(KeyboardContext context) {
    if (context.key == Key::Space) unpause();
}

void PauseController::pause() {
    level_ev_man.disable();
    pause_ev_man.enable();
}

void PauseController::unpause() {
    pause_ev_man.disable();
    level_ev_man.enable();
}



App::App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_):
    event_man(event_man_),
    pause_ev_man(),
    lvl(event_man_),
    pause_ctrl(lvl.getEventManager(), pause_ev_man),
    physics(),
    sprite_man(),
    graphics(w, h, sprite_man),
    sfwindow(sfwindow_) {
        lvl.getEventManager().CreateClockHandler(*this, &App::handleLevel);
        pause_ev_man.disable();
        event_man.addSubManager(pause_ev_man);
    }

void App::handleLevel(double dt) {
    physics.HandlePhysics(lvl, dt);
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