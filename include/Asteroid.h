#ifndef Asteroid_H
#define Asteroid_H

#include <cstdint>
#include <map>
#include <vector>

#include "UpdateData.h"
#include "GameObject.h"


enum class AsteroidType : uint8_t
{
    SMALL,
    BIG
};

class Asteroid : public GameObject
{
    public:
        Asteroid();
        Asteroid(const char* path);
        Asteroid(const AsteroidType);
        Asteroid(const U_Sprite&, const AsteroidType);
        virtual ~Asteroid();

        virtual void update(const UpdateData& data) override;
        virtual void unUpdate(const UpdateData& data) override;
        virtual std::vector<Asteroid>&& breakInPieces(const GameObject& obj);

        static constexpr float maxSpeed = 0.05f;
    protected:
        AsteroidType type;
    private:

};

#endif // Asteroid_H
