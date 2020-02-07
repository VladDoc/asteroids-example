#include <string>
#include <cmath>

#include "Framework.h"
#include "Player.h"
#include "Constants.h"
#include "util.h"

static const char* paths[] =
{
        "data\\spaceshipN.png",
        "data\\spaceshipNE.png",
        "data\\spaceshipE.png",
        "data\\spaceshipSE.png",
        "data\\spaceshipS.png",
        "data\\spaceshipSW.png",
        "data\\spaceshipW.png",
        "data\\spaceshipNW.png"
};

Player::Player() : GameObject(paths[0])
{

    angleSprites[0] = sprite_;
    for(int i = 1; i < angles; ++i) {
        angleSprites[i] = U_Sprite(paths[i]);
    }

    getScreenSize(sprite_.x, sprite_.y);

    sprite_.x -= sprite_.w;
    sprite_.y -= sprite_.h;

    sprite_.x /= 2;
    sprite_.y /= 2;

    position.x = sprite_.x;
    position.y = sprite_.y;

    current = (Sprite*)angleSprites[0].getSprite();
}

Player::Player(float x, float y, float angle) : GameObject(paths[0])
{
    sprite_angle = util::clampLooping(angle, 0.0f, 2 * Constants::pi);

    int whichSprite = sprite_angle / (Constants::pi / 4);

    current = (Sprite*)angleSprites[whichSprite].getSprite();

    accel = defAccel;

    position.x = x;
    position.y = y;

    sprite_.x = x;
    sprite_.y = y;
}

Player::~Player()
{

}

void Player::draw() const
{
    drawSprite(current, sprite_.x, sprite_.y);
}

void Player::update(const UpdateData& data)
{
    using namespace Constants;

    if(data.controls.isRightHeld) motionDelta.x += Player::defSpeed;
    if(data.controls.isLeftHeld)  motionDelta.x -= Player::defSpeed;
    if(data.controls.isUpHeld)    motionDelta.y -= Player::defSpeed;
    if(data.controls.isDownHeld)  motionDelta.y += Player::defSpeed;


    if(motionDelta.x == 0 &&
       motionDelta.y == 0) {
    } else {
        sprite_angle = util::vectorAngle(motionDelta.x, motionDelta.y);

        int whichSprite = (sprite_angle + 0.01) / (Constants::pi / 4);

        current = (Sprite*)angleSprites[whichSprite].getSprite();
    }
//    Vector2D<float> interpolated;
//    interpolated.x = util::interpolateValue(data.frametime, (float)motionDelta.x);
//    interpolated.y = util::interpolateValue(data.frametime, (float)motionDelta.y);
//
//    position = position + interpolated;
//
//    sprite_.x += position.x;
//    sprite_.y += position.y;

      data.setPlayer(this);
}

void Player::unUpdate(const UpdateData& data)
{

}

