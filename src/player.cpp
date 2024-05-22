#include "../include/player.hpp"


const Vec2 STAND_RIGHT = Vec2(0, 0);
const Vec2 STAND_LEFT  = Vec2(0, 1);
const Vec2   RUN_RIGHT = Vec2(1, 0);
const Vec2   RUN_LEFT  = Vec2(1, 1);

void Player::onKeyPress(KeyboardContext keyContext) {
    if (keyContext.key == Key::A) {
        setWalkingDir(LEFT);
        setFrame(RUN_LEFT);
    }
    if (keyContext.key == Key::D) {
        setWalkingDir(RIGHT);
        setFrame(RUN_RIGHT);
    }
    if (keyContext.key == Key::Space)
        setJumpFlag(true);
}

void Player::onKeyRelease(KeyboardContext keyContext){
    if (keyContext.key == Key::A)
        if (getWalkingDir() == LEFT) {
            setWalkingDir(STAND);
            setFrame(STAND_LEFT);
        }
    if (keyContext.key == Key::D)
        if (getWalkingDir() == RIGHT) {
            setWalkingDir(STAND);
            setFrame(STAND_RIGHT);
        }
    if (keyContext.key == Key::Space)
        setJumpFlag(false);
}
