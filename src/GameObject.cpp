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
    this->collision_radius = std::hypot(sprite_.w / 2, sprite_.h / 2) * 0.75f;
}


GameObject::GameObject(const U_Sprite& ref) : sprite_(ref)
{
    this->collision_radius = std::hypot(sprite_.w / 2, sprite_.h / 2) * 0.75f;
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

void GameObject::draw(const UpdateData& data) const
{
    if(sprite_.empty()) return;
    // Draw two sprites if object crosses the line
    Vector2D<float> overlap{0,0};

    Vector2D<float> screenSpaceOverlap;

    Vector2D<float> screenSpace;

    util::mapToScreenSpace(screenSpace, data.screenSize,
                           position, data.mapBoundaries);

    bool shouldDrawTwice = false;
    if((position.x + sprite_.w) > data.mapBoundaries.x)
    {
        overlap.x = position.x - data.mapBoundaries.x;
        shouldDrawTwice = true;
    }

    if((position.y + sprite_.h) > data.mapBoundaries.y)
    {
        overlap.y =  position.y - data.mapBoundaries.y;
        shouldDrawTwice = true;
    }


    drawSprite((Sprite*)sprite_.getSprite(),
                    screenSpace.x,
                    screenSpace.y);

    if(shouldDrawTwice) {
        util::mapToScreenSpace(screenSpaceOverlap,
                               data.screenSize, overlap,
                               data.mapBoundaries);
        drawSprite((Sprite*)sprite_.getSprite(),
                    overlap.x ? screenSpaceOverlap.x :
                                screenSpace.x,
                    overlap.y ? screenSpaceOverlap.y :
                                screenSpace.y);
    }
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

void GameObject::getCollisionRadius(float& value) const
{
    value = this->collision_radius;
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

void GameObject::setMiddlePoint(float x, float y)
{
    position.x = x - sprite_.w / 2;
    position.y = y - sprite_.h / 2;

    sprite_.x = (int)position.x;
    sprite_.y = (int)position.y;
}

void GameObject::getMiddlePoint(float& x, float& y) const
{
    x = position.x + sprite_.w / 2;
    y = position.y + sprite_.h / 2;
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


void GameObject::setMovement(const Vector2D<float>& speed,
                             const Vector2D<float>& acceleration)
{
    this->velocity = speed;
    this->accel = acceleration;
}

void GameObject::getMovement(Vector2D<float>& speed,
                             Vector2D<float>& acceleration) const
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
