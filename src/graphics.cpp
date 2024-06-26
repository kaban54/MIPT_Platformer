#include "../include/graphics.hpp"

GraphicsModule::GraphicsModule(unsigned int w, unsigned int h, SpriteManager& sprite_man_):
    screen(),
    sprite_man(sprite_man_) {
        screen.create(w, h);
        sprite_man.setScreenSize(w, h);
    }

static SpriteInfo getBackGroundInfo(const Background& bg, const Camera& cam);


void GraphicsModule::setFont(const sf::Font& fnt_) {
    fnt = fnt_;
}

void GraphicsModule::drawLevel(const Level& lvl) {
    const Camera cam = lvl.getCam();
    screen.draw(sprite_man.getSprite(Rect(Vec2(0, 0), cam.size),
                getBackGroundInfo(lvl.getBackground(), cam)));

    const std::vector<Drawable*> drawable = lvl.getDrawable();

    for (auto elem : drawable) {
        if (cam.canSee(elem))
            screen.draw(sprite_man.getSprite(*elem, cam));
    }

    #ifndef NDEBUG
    sf::RectangleShape player_frame(sf::Vector2f(cam.player_frame_size.x, cam.player_frame_size.y));
    player_frame.setPosition(cam.player_frame_pos.x, cam.player_frame_pos.y);
    player_frame.setOutlineColor(sf::Color::White);
    player_frame.setOutlineThickness(3);
    player_frame.setFillColor(sf::Color::Transparent);
    screen.draw(player_frame);

    sf::RectangleShape lvl_bounds(sf::Vector2f(lvl.getBounds().w, lvl.getBounds().h));
    lvl_bounds.setPosition(lvl.getBounds().x - cam.pos.x, lvl.getBounds().y - cam.pos.y);
    lvl_bounds.setOutlineColor(sf::Color::Red);
    lvl_bounds.setOutlineThickness(3);
    lvl_bounds.setFillColor(sf::Color::Transparent);
    screen.draw(lvl_bounds);
    #endif

    display();
}

void GraphicsModule::drawGui(const Gui& gui) {
    const Background& bg = gui.getBg();
    Camera cam (Vec2(screen.getSize().x, screen.getSize().y), Vec2(0, 0), Vec2(0, 0));
    cam.pos = Vec2(0, 0);
    screen.draw(sprite_man.getSprite(Rect(Vec2(0, 0), cam.size),
                getBackGroundInfo(bg, cam)));

    drawWidget(gui.getRoot());
    display();
}


void GraphicsModule::drawWidget(const Widget& wid) {
    if (!wid.getVisible()) return;
    if (wid.getSpriteInfo().textureID != NO_TEXTURE_ID) {
        if (wid.getSpriteInfo().textureID == TEXT_ID) drawText(*dynamic_cast<const Text*>(&wid));
        else screen.draw(sprite_man.getSprite(wid.getRect(), wid.getSpriteInfo()));
    }
    for (auto subwid : wid.getList()) drawWidget(*subwid);
}

void GraphicsModule::drawText(const Text& text) {
    sf::Text sftxt (text.getTxt(), fnt, text.getCharSize());
    sftxt.setPosition (text.getPos().x, text.getPos().y);
    sftxt.setFillColor (sf::Color::Black);
    screen.draw (sftxt);
    screen.display();
}

static SpriteInfo getBackGroundInfo(const Background& bg, const Camera& cam) {
    Vec2 bg_pos  = Vec2((int(cam.pos.x) % int(bg.size.x) + int(bg.size.x)) % int(bg.size.x), 0);
    return SpriteInfo(bg.textureID, bg_pos, cam.size);
}

void GraphicsModule::display() {
    screen.display();
}

void GraphicsModule::sfDisplay(sf::RenderWindow& window) const {
    sf::Sprite sprite;
    sprite.setTexture(screen.getTexture());
    sprite.setPosition(0, 0);
    window.draw(sprite);
}

