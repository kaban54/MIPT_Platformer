#ifndef JIJA_SPRITE_MAN_HPP
#define JIJA_SPRITE_MAN_HPP

#include <SFML/Graphics.hpp>
#include <string>
#include <unordered_map>
#include "camera.hpp"
#include "drawable.hpp"
#include "geometry.hpp"

class SpriteManager {
    public:

    explicit SpriteManager() = default;

    void loadTexture(uint64_t id, const std::string& filename);

    void reset();

    void setScreenSize(unsigned int screen_w_, unsigned int screen_h_);

    sf::Sprite getSprite(const Drawable& obj, const Camera& cam);

    sf::Sprite getSprite(const Rect& rect, const SpriteInfo& sprite_info);

    size_t getSize() const;

    private:
    std::unordered_map<uint64_t, sf::Texture> textures;
    unsigned int screen_w;
    unsigned int screen_h;
};

#endif