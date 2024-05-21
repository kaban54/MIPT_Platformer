#include "../include/sprite_man.hpp"

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
    return ret;
}

size_t SpriteManager::getSize() const {
    return textures.size();
}