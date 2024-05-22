#ifndef JIJA_DRAWABLE_HPP
#define JIJA_DRAWABLE_HPP

#include "objbase.hpp"


struct SpriteInfo {
    uint64_t textureID;
    Vec2 spritePos;
    Vec2 spriteSize;
    Vec2 frame;

    explicit SpriteInfo(uint64_t textureID_, Vec2 spritePos_, Vec2 spriteSize_):
    textureID (textureID_),
    spritePos (spritePos_),
    spriteSize (spriteSize_),
    frame (Vec2(0, 0))
    {}
};

class Drawable : public ObjBase {
    public:

    explicit Drawable(SpriteInfo info, Vec2 pos_, Vec2 size_):
    spriteInfo (info),
    pos (pos_),
    size (size_)
    {}

    Vec2 getPos()  const { return pos;  }
    Vec2 getSize() const { return size; }
    Rect getRect() const { return Rect(pos.x, pos.y, size.x, size.y); }

    void setPos  (Vec2      pos_) { pos  = pos_;  }
    void setSize (Vec2     size_) { size = size_; }

    void move (Vec2 delta) { pos += delta; }

    SpriteInfo  getSpriteInfo() const { return spriteInfo; }
    SpriteInfo& getSpriteInfo()       { return spriteInfo; }
    void setSpriteInfo(const SpriteInfo& info) {spriteInfo = info;}
    void setFrame(Vec2 frame_pos) { spriteInfo.frame = frame_pos; }
    void setTextureID(uint64_t id) { spriteInfo.textureID = id; }

    private:
    SpriteInfo spriteInfo;
    Vec2 pos;
    Vec2 size;
};

#endif