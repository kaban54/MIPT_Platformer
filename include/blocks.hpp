#ifndef JIJA_BLOCKS_HPP
#define JIJA_BLOCKS_HPP

#include "drawable.hpp"


struct BlockProperties {
    bool fixed;
    bool solid;

    explicit BlockProperties() = default;
    explicit BlockProperties(bool fixed_, bool solid_):
        fixed(fixed_),
        solid(solid_) {} 
};

class Block : public Drawable {
    public:

    explicit Block(SpriteInfo info, Vec2 pos_, Vec2 size_,
                   BlockProperties properties_ = BlockProperties()):
        Drawable(info, pos_, size_),
        prop(properties_) {}

    BlockProperties  properties() const { return prop; }
    BlockProperties& properties()       { return prop; }
    
    private:
    BlockProperties prop;
};

class FixedBlock : public Block {
    public:

    explicit FixedBlock(SpriteInfo info, Vec2 pos_, Vec2 size_):
        Block(info, pos_, size_) {
            properties().fixed = true;
            properties().solid = true;
        }
};



#endif