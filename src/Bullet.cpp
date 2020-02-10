#include "Bullet.h"
#include "Constants.h"
#include "Player.h"
#include "util.h"


static const char* path = "data\\bullet.png";

Bullet::Bullet() : GameObject(path)
{
    this->collision_radius *= 4;
}

Bullet::~Bullet()
{
}

void Bullet::update(const UpdateData& data)
{
    using namespace Constants;

    Vector2D<float> motionDelta;
    Vector2D<float> playersPos;

    data.player->getMiddlePoint(playersPos.x, playersPos.y);

    motionDelta.x = playersPos.x - data.mapBoundaries.x / 2;
    motionDelta.y = playersPos.y - data.mapBoundaries.y / 2;

    position = position - motionDelta;

    velocity.x += accel.x * data.frametime;
    velocity.y += accel.y * data.frametime;

    position = position + velocity;

    position.x = util::clampLooping(position.x, 0.0f, data.mapBoundaries.x);
    position.y = util::clampLooping(position.y, 0.0f, data.mapBoundaries.y);

    sprite_.x = (int)position.x;
    sprite_.y = (int)position.y;
}

void Bullet::unUpdate(const UpdateData& data)
{
    using namespace Constants;

    Vector2D<float> motionDelta;
    Vector2D<float> playersPos;

    data.player->getMiddlePoint(playersPos.x, playersPos.y);

    motionDelta.x = playersPos.x - data.mapBoundaries.x / 2;
    motionDelta.y = playersPos.y - data.mapBoundaries.y / 2;

    position = position + motionDelta;

    velocity.x -= accel.x * data.frametime;
    velocity.y -= accel.y * data.frametime;

    position = position + velocity;

    position.x = util::clampLooping(position.x, 0.0f, data.mapBoundaries.x);
    position.y = util::clampLooping(position.y, 0.0f, data.mapBoundaries.y);

    sprite_.x = (int)position.x;
    sprite_.y = (int)position.y;
}
