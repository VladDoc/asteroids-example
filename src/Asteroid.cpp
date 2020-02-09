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

//    sprite_.x -= motion.x;
//    sprite_.y -= motion.y;
}

void Asteroid::unUpdate(const UpdateData& data)
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


std::vector<Asteroid> Asteroid::breakInPieces(const GameObject& obj)
{
    if(this->type == AsteroidType::SMALL) {
        this->setEmpty(true);
        return std::vector<Asteroid>();
    } else {
        std::vector<Asteroid> asteroids;

        asteroids.push_back(Asteroid(this->getU_Sprite(), AsteroidType::SMALL));
        asteroids.push_back(Asteroid(this->getU_Sprite(), AsteroidType::SMALL));

        asteroids[0].setPosition(this->position.x, this->position.y);
        asteroids[1].setPosition(this->position.x, this->position.y);

        float angle = Constants::pi / ((float)rand() / (RAND_MAX + 1));

        float speed = 1.0f / ((float)rand() / (RAND_MAX + 1));

        Vector2D<float> obj_vel;
        Vector2D<float> obj_acc;

        obj.getMovement(obj_vel, obj_acc);

        float obj_angle = util::vectorAngle(obj_vel.x, obj_vel.y);

        asteroids[0].setMovement(
                util::lengthWithAngleToVector(obj_angle - angle, speed), {0,0});
        asteroids[1].setMovement(
                util::lengthWithAngleToVector(obj_angle + angle, speed), {0,0});

        return asteroids;
    }
}

bool operator<(const Asteroid& a, const Asteroid& b)
{
    Vector2D<float> a_pos;
    Vector2D<float> b_pos;

    a.getPosition(a_pos.x, a_pos.y);
    b.getPosition(b_pos.x, b_pos.y);

    return !a.empty() && a_pos < b_pos;
}
