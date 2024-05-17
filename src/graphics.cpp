#include "../include/graphics.hpp"


void SpriteManager::loadTexture(uint64_t id, const std::string& filename) {
    textures[id].loadFromFile(filename);
}

void SpriteManager::reset() {
    textures.clear();
}

void SpriteManager::setScreenSize(unsigned int screen_w_, unsigned int screen_h_) {
    screen_w = screen_w_;
    screen_h = screen_h_;
}

sf::Sprite SpriteManager::getSprite(const Drawable& obj, const Camera& cam) {
    sf::Sprite ret;
    Vec2 scale((double)screen_w / cam.size.x, (double)screen_h / cam.size.y);
    Vec2 pos = (obj.getPos() - cam.pos) ^ scale;
    Vec2 size = obj.getSize()           ^ scale;
    
    SpriteInfo info = obj.getSpriteInfo();
    sf::Texture& texture = textures[info.textureID];
    Vec2 frame_pos = info.spritePos + (info.frame ^ info.spriteSize); 

    ret.setPosition(pos.x, pos.y);
    ret.setTexture(texture);
    ret.setTextureRect(sf::IntRect(sf::Vector2<int>(frame_pos.x, frame_pos.y), sf::Vector2<int>(info.spriteSize.x, info.spriteSize.y)));
    ret.setScale(size.x / info.spriteSize.x, size.y / info.spriteSize.y);
    return ret;
}

sf::Sprite SpriteManager::getSprite(const Rect& rect, const SpriteInfo& info) {
    Vec2 pos  = rect.getPos();
    Vec2 size = rect.getSize();

    sf::Sprite ret;
    sf::Texture& texture = textures[info.textureID];
    Vec2 frame_pos = info.spritePos + (info.frame ^ info.spriteSize); 

    ret.setPosition(pos.x, pos.y);
    ret.setTexture(texture);
    ret.setTextureRect(sf::IntRect(sf::Vector2<int>(frame_pos.x, frame_pos.y), sf::Vector2<int>(info.spriteSize.x, info.spriteSize.y)));
    ret.setScale(size.x / info.spriteSize.x, size.y / info.spriteSize.y);
}


GraphicsModule::GraphicsModule(unsigned int w, unsigned int h, SpriteManager& sprite_man_):
    screen(),
    sprite_man(sprite_man_) {
        screen.create(w, h);
        sprite_man.setScreenSize(w, h);
    }

static SpriteInfo getBackGroundInfo(const Background& bg, const Camera& cam);

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

