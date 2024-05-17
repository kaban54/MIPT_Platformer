#include "../include/camera.hpp"

Camera::Camera(Vec2 size_, Vec2 player_frame_pos_, Vec2 player_frame_size_):
    pos(Vec2(0, 0)),
    size(size_),
    player_frame_pos(player_frame_pos_),
    player_frame_size(player_frame_size_),
    target(nullptr)
    {}
    
Camera::Camera(CameraParams params):
    pos(params.pos),
    size(params.size),
    player_frame_pos(params.player_frame_pos),
    player_frame_size(params.player_frame_size),
    target(nullptr)
    {}

Rect Camera::getRect() const {
    return Rect(pos.x, pos.y, size.x, size.y);
}

bool Camera::canSee(const Drawable* obj) const {
    return Intersect(obj->getRect(), getRect());
}

void Camera::followTarget(double) {
    if (target == nullptr) return;
    Rect frame(pos + player_frame_pos, player_frame_size); 
    Rect target_rect = target -> getRect();
    if (frame.contains(target_rect)) return;

    double dx = 0, dy = 0;
    if      (frame.left()  > target_rect.left() ) dx += (target_rect.left()  - frame.left());
    else if (frame.right() < target_rect.right()) dx += (target_rect.right() - frame.right());
    if      (frame.top()   > target_rect.top()  ) dy += (target_rect.top()   - frame.top());
    else if (frame.bot()   < target_rect.bot()  ) dy += (target_rect.bot()   - frame.bot());
    pos += Vec2(dx, dy);
}