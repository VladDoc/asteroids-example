#ifndef UPDATEDATA_H
#define UPDATEDATA_H


#include <ctime>
#include <memory>

#include "Vector2d.h"
#include "ControlState.h"

class Player;

class UpdateData
{
    public:
        UpdateData();
        virtual ~UpdateData();
        time_t frametime;

        Player* player;

        Vector2D<int> mouseMotionDelta;
        Vector2D<int> mouseCoords;
        Vector2D<int> mapBoundaries;
        Vector2D<int> screenSize;
        mutable ControlState controls; // Key presses

        mutable bool gameOver = false;
};

#endif // UPDATEDATA_H
