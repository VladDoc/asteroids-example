#include "BackGround.h"
#include "Vector2d.h"


static const char* path = "data\\background.png";

BackGround::BackGround() : background_(path)
{

}


BackGround::BackGround(const char* p) : background_(p)
{

}

BackGround::~BackGround()
{
}

void BackGround::draw()
{
    if(!background_.empty()) {
        Vector2D<int> screen;
        getScreenSize(screen.x, screen.y);
        const Sprite* bgSprite = background_.getSprite();
        for(int i = 0; i <= screen.x / background_.h + 1; ++i) {
            for(int j = 0; j <= screen.y / background_.w + 1; ++j) {
                drawSprite((Sprite*)bgSprite, j * background_.w, i * background_.h);
            }
        }
    }
}

void BackGround::setSprite(const U_Sprite& sprite)
{
    background_ = sprite;
}

void BackGround::setSprite(const char* p)
{
    U_Sprite temp(p);
    background_ = temp;
}
