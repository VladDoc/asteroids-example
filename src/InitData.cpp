#include "InitData.h"

#include <cstring>
#include <cstdio>

InitData::InitData(int argc, char** argv)
    : windowSize(800, 600),
      mapSize(800, 600),
      num_asteroids(10),
      num_ammo(3),
      ability_probability(0.3f)
{
    for(int i = 1; i < argc; i+=2) {
        if(strcmp(argv[i], "window")) {
            sscanf(argv[i+1], "%dx%d",
                   &windowSize.x,
                   &windowSize.y);
           continue;
        }

        if(strcmp(argv[i], "map")) {
            sscanf(argv[i+1], "%dx%d",
                   &mapSize.x,
                   &mapSize.y);
           continue;
        }

        if(strcmp(argv[i], "num_asteroids")) {
            sscanf(argv[i+1], "%d", &num_asteroids);
           continue;
        }

        if(strcmp(argv[i], "num_ammo")) {
            sscanf(argv[i+1], "%d", &num_ammo);
           continue;
        }

        if(strcmp(argv[i], "ability_probability")) {
            sscanf(argv[i+1], "%d", &ability_probability);
           continue;
        }
    }
}
