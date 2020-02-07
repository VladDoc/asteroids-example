#ifndef PLAYER_H
#define PLAYER_H

#include "GameObject.h"
#include "U_Sprite.h"
#include "Framework.h"

class Player : public GameObject
{
    public:
        Player();
        Player(float x, float y, float angle);
        ~Player();

        virtual void update(const UpdateData& data) override;
        virtual void unUpdate(const UpdateData& data) override;
        virtual void draw() const override;


        constexpr static const float defSpeed = 1.0f;
        constexpr static const float defAccel = 1.5f;
    protected:
        static const int angles = 8;
        U_Sprite angleSprites[angles];
        Sprite* current;
        Vector2D<int> motionDelta;
    private:

};

#endif // PLAYER_H
