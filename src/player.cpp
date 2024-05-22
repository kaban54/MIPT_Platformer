#include "../include/player.hpp"

const double BASE_SPEED = 100;

const Vec2  LEFT_FRAME = Vec2(-1, 0);
const Vec2 STAND_FRAME = Vec2(0, 0);
const Vec2 RIGHT_FRAME = Vec2(1, 0);

void Player::onKeyPress(KeyboardContext keyContext) {
    if (keyContext.key == Key::A) {
        setWalkingDir(LEFT);
        // setFrame(LEFT_FRAME);
    }
    if (keyContext.key == Key::D) {
        setWalkingDir(RIGHT);
        // setFrame(RIGHT_FRAME);
    }
    if (keyContext.key == Key::Space)
        setJumpFlag(true);
}

void Player::onKeyRelease(KeyboardContext keyContext){
    if (keyContext.key == Key::A)
        if (getWalkingDir() == LEFT) {
            setWalkingDir(STAND);
            // setFrame(STAND_FRAME);
        }
    if (keyContext.key == Key::D)
        if (getWalkingDir() == RIGHT) {
            setWalkingDir(STAND);
            // setFrame(STAND_FRAME);
        }
    if (keyContext.key == Key::Space)
        setJumpFlag(false);
}
