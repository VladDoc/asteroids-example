#ifndef INITDATA_H
#define INITDATA_H

#include "Vector2d.h"

struct InitData
{
    Vector2D<int> windowSize;
    Vector2D<int> mapSize;

    int num_asteroids;
    int num_ammo;

    float ability_probability;

    InitData(int argc, char** argv);
};

#endif // INITDATA_H
