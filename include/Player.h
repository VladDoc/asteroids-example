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
        virtual void draw(const UpdateData& data) const override;

        virtual size_t getCurrentSpriteIndex() const final;

        constexpr static const float defAccel = 0.1f;
        constexpr static const float maxSpeed = 0.4f;
    protected:
        static const int angles = 8;
        U_Sprite angleSprites[angles];
        size_t current;
        Vector2D<float> motionDelta;
    private:

};

#endif // PLAYER_H
