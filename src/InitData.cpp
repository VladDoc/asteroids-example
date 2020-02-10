#include "InitData.h"

#include <cstring>
#include <cstdio>

InitData::InitData(int argc, char** argv)
    : windowSize(800, 600),
      mapSize(800, 600),
      num_asteroids(50),
      num_ammo(3),
      ability_probability(0.3f)
{
    for(int i = 1; i < argc-1; i+=2) {
        if(strcmp(argv[i], "window") == 0) {
            sscanf(argv[i+1], "%dx%d",
                   &windowSize.x,
                   &windowSize.y);
           continue;
        }

        if(strcmp(argv[i], "map") == 0) {
            sscanf(argv[i+1], "%dx%d",
                   &mapSize.x,
                   &mapSize.y);
           continue;
        }

        if(strcmp(argv[i], "num_asteroids") == 0) {
            sscanf(argv[i+1], "%d", &num_asteroids);
           continue;
        }

        if(strcmp(argv[i], "num_ammo") == 0) {
            sscanf(argv[i+1], "%d", &num_ammo);
           continue;
        }

        if(strcmp(argv[i], "ability_probability") == 0) {
            sscanf(argv[i+1], "%f", &ability_probability);
           continue;
        }
    }
}
