#ifndef BULLET_H
#define BULLET_H

#include "GameObject.h"


class Bullet : public GameObject
{
    public:
        Bullet();
        virtual ~Bullet();

        virtual void update(const UpdateData&) override;
        virtual void unUpdate(const UpdateData&) override;
    protected:
    private:
};

#endif // BULLET_H