#include "Bullet.h"
#include "Constants.h"
#include "Player.h"


static const char* path = "data\\bullet.png";

Bullet::Bullet() : GameObject(path)
{
}

Bullet::~Bullet()
{
}

void Bullet::update(const UpdateData& data)
{
    using namespace Constants;

    Vector2D<int> motionDelta;

    if(data.controls.isRightHeld) motionDelta.x =  Player::defSpeed;
    if(data.controls.isLeftHeld)  motionDelta.x = -Player::defSpeed;
    if(data.controls.isUpHeld)    motionDelta.y = -Player::defSpeed;
    if(data.controls.isDownHeld)  motionDelta.y =  Player::defSpeed;

    position = position - motionDelta;

    velocity.x += accel * data.frametime;
    velocity.y += accel * data.frametime;

    position = position + velocity;

    sprite_.x = (int)position.x;
    sprite_.y = (int)position.y;
}

void Bullet::unUpdate(const UpdateData& data)
{
    using namespace Constants;

    Vector2D<int> motionDelta;

    if(data.controls.isRightHeld) motionDelta.x =  Player::defSpeed;
    if(data.controls.isLeftHeld)  motionDelta.x = -Player::defSpeed;
    if(data.controls.isUpHeld)    motionDelta.y = -Player::defSpeed;
    if(data.controls.isDownHeld)  motionDelta.y =  Player::defSpeed;

    position = position + motionDelta;

    velocity.x += accel * data.frametime;
    velocity.y += accel * data.frametime;

    position = position - velocity;

    sprite_.x = (int)position.x;
    sprite_.y = (int)position.y;
}
