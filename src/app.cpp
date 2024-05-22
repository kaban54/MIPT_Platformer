#include "../include/app.hpp"

AppController::AppController(App& app_):
    app(app_)
    {
        app.lvl.getEventManager().CreateKeyPressHandler(*this, &AppController::onLevelKey);

        Button* unpause_btn = new Button(Vec2(app.size.x / 2 - 300, 400), Vec2(600, 75));
        unpause_btn -> addReleasingHandler(*this, &AppController::unpause);
        app.pause_menu.getRoot().pushFrontSubWidget(unpause_btn);
        Button* exit_btn = new Button(Vec2(app.size.x / 2 - 300, 500), Vec2(600, 75));
        exit_btn -> addReleasingHandler(*this, &AppController::exit);
        app.pause_menu.getRoot().pushFrontSubWidget(exit_btn);

        Text* play_txt = new Text(Vec2(app.size.x / 2 - 62, 400), "PLAY", 60);
        unpause_btn -> pushFrontSubWidget(play_txt);
        Text* exit_txt = new Text(Vec2(app.size.x / 2 - 62, 500), "EXIT", 60);
        exit_btn -> pushFrontSubWidget(exit_txt);
    }

void AppController::onLevelKey(KeyboardContext context) {
    if (context.key == Key::Escape) pause();
}

void AppController::pause() {
    app.lvl.getEventManager().disable();
    app.pause_menu.getEventMan().enable();
    app.level_active = false;
}

void AppController::unpause() {
    app.pause_menu.getEventMan().disable();
    app.lvl.getEventManager().enable();
    app.level_active = true;
}

void AppController::exit() {
    app.sfwindow.close();
}



App::App(unsigned int w, unsigned int h, EventManager& event_man_, sf::RenderWindow& sfwindow_):
    size(w, h),
    event_man(event_man_),
    pause_menu(event_man_, w, h),
    lvl(event_man_),
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
        #ifdef WIND
        full_name.assign("plugins/windows");
        #else
        full_name.assign("plugins/linux");
        #endif
        
        full_name += plugin_name;
        obj_man.loadPlugin(full_name);
    }
}

void App::loadLevel(const std::string& filename) {
    lvl.load(filename, obj_man, sprite_man);
}

void App::loadFont(const std::string& filename) {
    sf::Font fnt;
    fnt.loadFromFile(filename);
    graphics.setFont(fnt);
}