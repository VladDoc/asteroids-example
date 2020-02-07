#pragma once

#ifndef ASTEROIDFIELD_H
#define ASTEROIDFIELD_H

#include <vector>

#include "include/GameObject.h"


class AsteroidField : public GameObject
{
    public:
        explicit AsteroidField(int qty);
        AsteroidField();
        virtual ~AsteroidField();

        virtual void update() override;
        virtual void draw() override;
        virtual void render(int posX, int posY);
    protected:
        std::vector<Asteroid> asteroids;
    private:
};

#endif // ASTEROIDFIELD_H
