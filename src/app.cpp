#include "../include/app.hpp"

PauseController::PauseController(EventManager& lvl, EventManager& pause, bool& lvl_active):
    level_active (lvl_active),
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
    level_active = false;
}

void PauseController::unpause() {
    pause_ev_man.disable();
    level_ev_man.enable();
    level_active = true;
}



App::App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_):
    event_man(event_man_),
    pause_menu(event_man_, w, h),
    lvl(event_man_),
    pause_ctrl(lvl.getEventManager(), pause_menu.getEventMan(), level_active),
    physics(),
    sprite_man(),
    graphics(w, h, sprite_man),
    sfwindow(sfwindow_),
    active_gui(pause_menu),
    level_active(false) {
        sprite_man.loadTexture(BUTTON_TEXTURE_ID, "textures/button.png");
        sprite_man.loadTexture(GUI_BG_TEXTURE_ID, "textures/background4.png");
        event_man.CreateClockHandler(*this, &App::onClock);
        lvl.getEventManager().disable();
    }

void App::onClock(double dt) {
    if (level_active) handleLevel(dt);
    else              handleGui  (dt);
}

void App::handleLevel(double dt) {
    physics.HandlePhysics(lvl, dt);
    graphics.drawLevel(lvl);
    graphics.sfDisplay(sfwindow);
}

void App::handleGui(double dt) {
    graphics.drawGui(active_gui);
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