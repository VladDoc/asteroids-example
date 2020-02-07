#ifndef MAP_H
#define MAP_H

#include <vector>

#include "UpdateData.h"
#include "Asteroid.h"


class Map
{
    public:
        Map(int asteroids_qty, int max_bullets);
        virtual ~Map();


        virtual void update(const UpdateData& data);
    protected:
        std::vector<Asteroid> asteroids;
        //std::vector<>
    private:
};

#endif // MAP_H
