#include <type_traits>

#include "GameObject.h"
#include "Framework.h"
#include "util.h"
#include "Constants.h"


GameObject::GameObject()
{
    //ctor
}


GameObject::GameObject(const char* sprite_path) : sprite_(sprite_path)
{
    this->collision_radius = std::hypot(sprite_.w / 2, sprite_.h / 2);
}


GameObject::GameObject(const U_Sprite& ref) : sprite_(ref)
{
    this->collision_radius = std::hypot(sprite_.w / 2, sprite_.h / 2);
}


GameObject::~GameObject()
{

}


bool GameObject::checkCollision(const GameObject& another) const
{
    int x1, y1;
    int x2, y2;

    sprite_.getMiddlePoint(x1, y1);
    another.getU_Sprite().getMiddlePoint(x2, y2);

    int dx = x1 - x2;
    int dy = y1 - y2;

    float distance = std::hypot(dx, dy);

    if(distance < this->collision_radius + another.collision_radius) {
        return true;
    }

    return false;
}


void GameObject::draw() const
{
    sprite_.draw();
}


bool GameObject::empty() const
{
    return sprite_.empty();
}

void GameObject::setEmpty(bool flag)
{
    sprite_.setEmpty(flag);
}

const U_Sprite& GameObject::getU_Sprite() const
{
    return this->sprite_;
}

void GameObject::setCollisionRadius(float value)
{
    this->collision_radius = value;
}

void GameObject::setPosition(float x, float y)
{
    position.x = x;
    position.y = y;

    sprite_.x = (int)x;
    sprite_.y = (int)y;

}

void GameObject::getPosition(float& x, float& y) const
{
    x = position.x;
    y = position.y;
}

void GameObject::setSprite(const U_Sprite& sprite)
{
    this->sprite_ = sprite;
}

void GameObject::setSprite(const char* path)
{
    U_Sprite sprite(path);
    this->sprite_ = sprite;
}


void GameObject::setMovement(Vector2D<float> speed,
                             float acceleration)
{
    this->velocity = speed;
    this->accel = acceleration;
}

void GameObject::getMovement(Vector2D<float>& speed,
                             float& acceleration) const
{
    speed = this->velocity;
    acceleration = this->accel;
}

void GameObject::setRotation(float speed,
                             float acceleration,
                             float start_angle)
{
    this->angular_velocity = speed;
    this->angular_accel = acceleration;
    this->sprite_angle = start_angle;
}

void GameObject::getRotation(float& speed,
                             float& acceleration,
                             float& start_angle) const
{
    speed = this->angular_velocity;
    acceleration = this->angular_accel;
    start_angle = this->sprite_angle;
}

void GameObject::setMass(float mass)
{
    this->mass = mass;
}

void GameObject::getMass(float& m) const
{
    m = this->mass;
}
