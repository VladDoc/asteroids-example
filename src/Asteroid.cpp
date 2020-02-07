#include <cstdlib>
#include <cmath>

#include "Asteroid.h"
#include "Constants.h"
#include "util.h"
#include "Player.h"



static const std::map<const AsteroidType, std::string> asteroidSpritePaths =
{
        {AsteroidType::BIG, "data\\big_asteroid.png"},
        {AsteroidType::SMALL, "data\\small_asteroid.png"}
};

Asteroid::Asteroid()
{

}

Asteroid::Asteroid(const char* path) :
    GameObject(path)
{
    if(path == asteroidSpritePaths.at(AsteroidType::SMALL)) {
        this->type = AsteroidType::SMALL;
    } else {
        this->type = AsteroidType::BIG;
    }
}

Asteroid::Asteroid(const AsteroidType type) :
    GameObject(asteroidSpritePaths.at(type).c_str())
{
    this->type = type;
}

Asteroid::Asteroid(const U_Sprite& sprite, const AsteroidType type) :
    GameObject(sprite)
{
    this->type = type;
}

Asteroid::~Asteroid()
{

}

void Asteroid::update(const UpdateData& data)
{
    using namespace Constants;

    if(data.controls.isRightHeld) motionDelta.x += Player::defSpeed;
    if(data.controls.isLeftHeld)  motionDelta.x -= Player::defSpeed;
    if(data.controls.isUpHeld)    motionDelta.y -= Player::defSpeed;
    if(data.controls.isDownHeld)  motionDelta.y += Player::defSpeed;

    position = position - motionDelta;

    velocity.x += accel * data.frametime;
    velocity.y += accel * data.frametime;

    position = position + velocity;

    sprite_.x = (int)position.x;
    sprite_.y = (int)position.y;

//    sprite_.x -= motion.x;
//    sprite_.y -= motion.y;
}

void Asteroid::unUpdate(const UpdateData& data)
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


std::vector<Asteroid>&& Asteroid::breakInPieces(const GameObject& obj)
{
    if(this->type == AsteroidType::SMALL) {
        this->setEmpty(true);
        std::move(std::vector<Asteroid>());
    } else {
        std::vector<Asteroid> asteroids;

        asteroids.push_back(Asteroid(this->getU_Sprite(), AsteroidType::SMALL));
        asteroids.push_back(Asteroid(this->getU_Sprite(), AsteroidType::SMALL));

        asteroids[0].setPosition(this->position.x, this->position.y);
        asteroids[1].setPosition(this->position.x, this->position.y);

        float angle = Constants::pi / ((float)rand() / (RAND_MAX + 1));

        float speed = 1.0f / ((float)rand() / (RAND_MAX + 1));

        Vector2D<float> obj_vel;
        float whatever;

        obj.getMovement(obj_vel, whatever);

        float obj_angle = util::vectorAngle(obj_vel.x, obj_vel.y);

        asteroids[0].setMovement(
                util::lengthWithAngleToVector(obj_angle - angle, speed), 0.0f);
        asteroids[1].setMovement(
                util::lengthWithAngleToVector(obj_angle + angle, speed), 0.0f);

        std::move(asteroids);
    }
}
