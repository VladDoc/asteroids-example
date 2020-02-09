#include "Map.h"

#include <random>

#include "util.h"

Map::Map(int asteroids_qty, int max_bullets,
         const Vector2D<int>& mapSize,
         const Player& player)
{
    this->mapSize = mapSize;

    this->bullets.resize(max_bullets, Bullet());

    for(auto& a : bullets) {
        a.setEmpty(true);
    }

    this->asteroids.reserve(asteroids_qty);

    float playerWidth;
    player.getCollisionRadius(playerWidth);
    playerWidth *= 3;

    Vector2D<float> playerPos;
    player.getMiddlePoint(playerPos.x, playerPos.y);

    int density = (mapSize.y - (int)playerWidth) * (mapSize.x - (int)playerWidth) / asteroids_qty;



    std::uniform_int_distribution<int> distint(1, 4);
    std::uniform_real_distribution<float> distfloat(-Asteroid::maxSpeed,
                                                     Asteroid::maxSpeed);
    std::mt19937 random;

    U_Sprite small("data\\small_asteroid.png");
    U_Sprite big("data\\big_asteroid.png");
    for(int i = 0; i < mapSize.y * mapSize.x; i += density) {
        Vector2D<int> mapIndeces;
        util::oneIndexIntoTwo(i, mapSize.x, mapIndeces.y, mapIndeces.x);

        if(util::withinArea(mapIndeces, (Vector2D<int>)playerPos, playerWidth)) {
            continue;
        }

        if(distint(random) == 1) {
            asteroids.push_back(Asteroid(big, AsteroidType::BIG));
        } else {
            asteroids.push_back(Asteroid(small, AsteroidType::SMALL));
        }

        asteroids.back().setPosition(mapIndeces.x, mapIndeces.y);
        asteroids.back().setMovement({distfloat(random), distfloat(random)},
                                     {0,0});
    }
}

Map::~Map()
{
    //dtor
}

void Map::update(const UpdateData& data)
{
    for(auto& a : asteroids) {
        a.update(data);
    }

    for(auto& a : bullets) {
        a.update(data);
    }

}

void Map::draw(const UpdateData& data)
{
    for(auto& a : asteroids) {
        a.draw(data);
    }

    for(auto& a : bullets) {
        a.draw(data);
    }
}
