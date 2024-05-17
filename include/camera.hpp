#ifndef JIJA_CAM_HPP
#define JIJA_CAM_HPP

#include "geometry.hpp"
#include "drawable.hpp"

struct CameraParams {
    Vec2 pos;
    Vec2 size;
    Vec2 player_frame_pos;
    Vec2 player_frame_size;

    CameraParams(Vec2 pos_, Vec2 size_, Vec2 player_frame_pos_, Vec2 player_frame_size_):
        pos(pos_),
        size(size_),
        player_frame_pos(player_frame_pos_),
        player_frame_size(player_frame_size_)
        {}
};

struct Camera {
    Vec2 pos;
    Vec2 size;
    Vec2 player_frame_pos;
    Vec2 player_frame_size;
    Drawable* target;

    explicit Camera() = default;
    explicit Camera(Vec2 size_, Vec2 player_frame_pos_, Vec2 player_frame_size_);
    explicit Camera(CameraParams params);
    
    Rect getRect() const;

    bool canSee(const Drawable* obj) const;

    void followTarget(double);
};

#endif