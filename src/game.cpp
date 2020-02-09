#include <cstdlib>
#include <cmath>
#include <memory>
#include <ctime>

#include "Framework.h"
#include "BackGround.h"
#include "U_Sprite.h"
#include "Asteroid.h"
#include "UpdateData.h"
#include "Player.h"
#include "Constants.h"
#include "stdoutRedirect.h"
#include "Map.h"

/* Test Framework realization */
class MyFramework : public Framework {

    std::unique_ptr<BackGround> bg;

    std::unique_ptr<Player> player;

    std::unique_ptr<U_Sprite> cursor;

    std::unique_ptr<Map> map;

    UpdateData upData;

    ControlState state;
public:

    virtual void PreInit(int& width, int& height, bool& fullscreen)
    {
        width = 800;
        height = 600;
        fullscreen = false;
    }

    // Load up data
    virtual bool Init() {

        showCursor(false);

        bg = std::make_unique<BackGround>();

        player = std::make_unique<Player>();
        player->setMiddlePoint(400, 300);

        cursor = std::make_unique<U_Sprite>("data/circle.tga");

        upData.mapBoundaries.x = 800;
        upData.mapBoundaries.y = 600;

        map = std::make_unique<Map>(10, 2, upData.mapBoundaries, *player);

        upData.frametime = 15;
        upData.player = player.get();
        upData.controls.leftMouseButton = true;

        getScreenSize(upData.mapBoundaries.x, upData.mapBoundaries.y);

        return true;
    }

    virtual void Close()
    {
        Map& aMap = *map;
    }

    // Update
    virtual bool Tick() {

        time_t start = clock();
        bg->draw();

        player->update(upData);

        player->draw();

        map->update(upData);

        map->draw(upData);

        if(upData.gameOver) {
           return true;
        }

        cursor->x = upData.mouseCoords.x - cursor->w / 2;
        cursor->y = upData.mouseCoords.y - cursor->h / 2;

        cursor->draw();

        time_t end = clock();

        upData.frametime = (end - start) > 16 ? (end - start) : 16;
        return false;
    }

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative)
    {
        upData.mouseCoords.x = x;
        upData.mouseCoords.y = y;

        upData.mouseMotionDelta.x = xrelative;
        upData.mouseMotionDelta.y = yrelative;
    }

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

        if (button == FRMouseButton::LEFT && !isReleased)
        {
            upData.controls.leftMouseButton = true;
        }

        if (button == FRMouseButton::RIGHT && !isReleased)
        {
            upData.controls.rightMouseButton = true;
        }

    }

    virtual void onKeyPressed(FRKey k) {

        onKey(k);
    }

    virtual void onKeyReleased(FRKey k)
    {
        switch (k)
        {
        case FRKey::LEFT:
            upData.controls.isLeftHeld = false;
            break;
        case FRKey::RIGHT:
            upData.controls.isRightHeld = false;
            break;
        case FRKey::DOWN:
            upData.controls.isDownHeld = false;
            break;
        case FRKey::UP:
            upData.controls.isUpHeld = false;
            break;
        }
    }

protected:
    void onKey(FRKey k)
    {
        switch (k)
        {
        case FRKey::LEFT:
            upData.controls.isLeftHeld = true;
            break;
        case FRKey::RIGHT:
            upData.controls.isRightHeld = true;
            break;
        case FRKey::DOWN:
            upData.controls.isDownHeld = true;
            break;
        case FRKey::UP:
            upData.controls.isUpHeld = true;
            break;
        }

    }


    virtual const char* GetTitle() override
    {
        return "asteroids";
    }
};


int main(int argc, char *argv[])
{

    switchStderr("errors.txt");
    return run(new MyFramework);
}
