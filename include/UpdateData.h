#ifndef UPDATEDATA_H
#define UPDATEDATA_H

#include <ctime>
#include "Vector2d.h"
#include "ControlState.h"

class Player;

class UpdateData
{
    public:
        UpdateData();
        virtual ~UpdateData();
        time_t frametime;


        virtual void setPlayer(Player* p) const final;

        mutable Player* player;
        Vector2D<int> mouseMotionDelta;
        Vector2D<int> mouseCoords;
        ControlState controls; // Key presses
};

#endif // UPDATEDATA_H
