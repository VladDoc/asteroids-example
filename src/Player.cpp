#include <string>
#include <cmath>
#include <limits>

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

    current = 0;

    //collision_radius *= 0.65;
}

Player::Player(float x, float y, float angle) : GameObject(paths[0])
{
    sprite_angle = util::clampLooping(angle, 0.0f, 2 * Constants::pi);

    int whichSprite = sprite_angle / (Constants::pi / 4);

    current = whichSprite;

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
    drawSprite((Sprite*)angleSprites[current].getSprite(),
                sprite_.x, sprite_.y);
}

void Player::draw(const UpdateData& data) const
{
    // Draw two sprites if object crosses the line
    Vector2D<int> overlap{0,0};
    if((sprite_.x + angleSprites[current].w) > data.mapBoundaries.x)
    {
        overlap.x = sprite_.x - data.mapBoundaries.x;
    }

    if((sprite_.y + angleSprites[current].h) > data.mapBoundaries.y)
    {
        overlap.y = sprite_.y - data.mapBoundaries.y;
    }
    drawSprite((Sprite*)angleSprites[current].getSprite(),
                    sprite_.x, sprite_.y);

    drawSprite((Sprite*)angleSprites[current].getSprite(),
               overlap.x ? overlap.x : sprite_.x,
               overlap.y ? overlap.y : sprite_.y);
}

void Player::update(const UpdateData& data)
{
    using namespace Constants;

    if(data.controls.isRightHeld) {
        sprite_angle += util::interpolateValue(data.frametime,
                                               util::degToRad(45.0f));
    }
    if(data.controls.isLeftHeld)  {
        sprite_angle -= util::interpolateValue(data.frametime,
                                               util::degToRad(45.0f));
    }

    sprite_angle = util::clampLooping(sprite_angle, 0.0f,
                                      2 * pi - 0.00001); // For extra safety

    if(data.controls.isUpHeld)    {
        accel.x = util::interpolateValue(data.frametime,
                                          sinf(sprite_angle) * defAccel);
        accel.y = util::interpolateValue(data.frametime,
                                         -cosf(sprite_angle) * defAccel);
    }
    if(data.controls.isDownHeld)  {
        accel.x = util::interpolateValue(data.frametime,
                                         -sinf(sprite_angle) * defAccel);
        accel.y = util::interpolateValue(data.frametime,
                                          cosf(sprite_angle) * defAccel);
    }

    velocity = velocity + accel;

    accel.x = 0;
    accel.y = 0;

    velocity.x = util::clamp(velocity.x, -maxSpeed, maxSpeed);
    velocity.y = util::clamp(velocity.y, -maxSpeed, maxSpeed);

    motionDelta.x = velocity.x;
    motionDelta.y = velocity.y;

    motionDelta.x = util::interpolateValue(data.frametime, motionDelta.x);
    motionDelta.y = util::interpolateValue(data.frametime, motionDelta.y);


    position = position + motionDelta;

    position.x = util::clampLooping(position.x, 0.0f, data.mapBoundaries.x);
    position.y = util::clampLooping(position.y, 0.0f, data.mapBoundaries.y);

    int whichSprite = (sprite_angle) / (Constants::pi / 4);

    //whichSprite = util::clampLooping(whichSprite, 0, angles-1);

    current = whichSprite;

    //if(position.x < data.)

//    sprite_.x = position.x;
//    sprite_.y = position.y;

}

void Player::unUpdate(const UpdateData& data)
{

}

