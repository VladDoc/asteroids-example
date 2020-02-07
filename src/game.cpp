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

/* Test Framework realization */
class MyFramework : public Framework {

    Sprite* ava_;
    Sprite* enemy_;
    Sprite* reticle_;
    Sprite* bullet_;


    int as_w, as_h;
    int es_w, es_h;
    int rs_w, rs_h;
    int bs_w, bs_h;

    int r_x;
    int r_y;

    int ava_pos_x;
    int ava_pos_y;

    float b_x, b_y;
    float b_dir_x, b_dir_y;
    bool is_bullet_active;

    static const int sNumEnemies = 16;
    int e_x[sNumEnemies];
    int e_y[sNumEnemies];
    bool alive_[sNumEnemies];

    int last_mouse_x;
    int last_mouse_y;

    std::unique_ptr<BackGround> bg;

    std::unique_ptr<Asteroid> asteroid;

    std::unique_ptr<Player> player;

    std::unique_ptr<U_Sprite> cursor;

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

        int sx, sy;
        getScreenSize(sx, sy);

        showCursor(false);

        asteroid = std::make_unique<Asteroid>(AsteroidType::SMALL);

        asteroid->setPosition(40, 40);
        asteroid->setMovement(Vector2D<float>{0, 0}, 0);

        bg = std::make_unique<BackGround>();

        player = std::make_unique<Player>();
        player->setRotation(0.0f, 0.0f, 0.0f);

        player->setPosition(400, 300);

        cursor = std::make_unique<U_Sprite>("data/circle.tga");
        upData.frametime = 15;


        enemy_ = createSprite("data/small_asteroid.png");
        reticle_ = createSprite("data/circle.tga");
        bullet_ = createSprite("data/bullet.png");

        if (!reticle_ || !ava_ || ! enemy_ || !bullet_)
            return false;

        getSpriteSize(enemy_, es_w, es_h);
        getSpriteSize(reticle_, rs_w, rs_h);
        getSpriteSize(bullet_, bs_w, bs_h);

        for (int i = 0; i < sNumEnemies; i++)
        {
            e_x[i] = rand() % sx;
            e_y[i] = rand() % sy;
            alive_[i] = true;
        }

        ava_pos_x = sx / 2;
        ava_pos_y = sy / 2;

        r_x = ava_pos_x;
        r_y = ava_pos_y;

        b_x = b_y = 0;
        is_bullet_active = false;
        b_dir_x = b_dir_y = 1;

        return true;
    }

    virtual void Close() {

        //destroySprite(ava_);
        destroySprite(enemy_);
        destroySprite(reticle_);
    }

    // Update
    virtual bool Tick() {

        time_t start = clock();
        bg->draw();

        asteroid->update(upData);

        asteroid->draw();


        player->update(upData);

        player->draw();

        cursor->x = upData.mouseCoords.x - cursor->w / 2;
        cursor->y = upData.mouseCoords.y - cursor->h / 2;

        cursor->draw();

        bool should_exit = true;
        for (int i = 0; i < sNumEnemies; ++i)
        {
            if (alive_[i])
            {
                int offset_y = (int)(30*sinf(getTickCount()*0.01f + e_x[i]));
                //drawSprite(enemy_, e_x[i] - es_w / 2, e_y[i] - es_w / 2 + offset_y);
                should_exit = false;
            }
        }

        //drawSprite(reticle_, r_x - rs_w / 2, r_y - rs_h / 2);

        if (is_bullet_active)
        {
            const float speed = 1.5f;

            b_x = b_x + b_dir_x * speed;
            b_y = b_y + b_dir_y * speed;

            int sx, sy;
            getScreenSize(sx, sy);

            if (b_x < 0 || b_x > sx)
                is_bullet_active = false;

            if (b_y < 0 || b_y > sy)
                is_bullet_active = false;
        }

        if (is_bullet_active)
        {
            drawSprite(bullet_, (int)b_x - bs_w / 2, (int)b_y - bs_h / 2);
        }

        time_t end = clock();

        upData.frametime = (end - start) > 16 ? (end - start) : 16;
        return should_exit;
    }

    virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

        r_x = x;
        r_y = y;

        upData.mouseCoords.x = x;
        upData.mouseCoords.y = y;

        upData.mouseMotionDelta.x = xrelative;
        upData.mouseMotionDelta.y = yrelative;
    }

    virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

        float rx = (float)r_x;
        float ry = (float)r_y;
        if (button == FRMouseButton::LEFT && !isReleased)
        {
            for (int i = 0; i < sNumEnemies; ++i)
            {
                if (!alive_[i])
                    continue;

                float x = (float)e_x[i];
                float y = (float)e_y[i];

                float dist_sq = (rx - x)*(rx - x) + (ry - y)*(ry - y);

                if (dist_sq < 10 * 10)
                {
                    alive_[i] = false;
                    continue;
                }
            }
        }

        if (button == FRMouseButton::RIGHT && !isReleased)
        {
            b_x = (float)ava_pos_x;
            b_y = (float)ava_pos_y;
            b_dir_x = (float)(rx - b_x);
            b_dir_y = (float)(ry - b_y);

            // normalize
            float len = sqrtf(b_dir_x*b_dir_x + b_dir_y*b_dir_y);
            b_dir_x = b_dir_x / len;
            b_dir_y = b_dir_y / len;

            is_bullet_active = true;
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
            ava_pos_x -= 10;
            upData.controls.isLeftHeld = true;
            break;
        case FRKey::RIGHT:
            ava_pos_x += 10;
            upData.controls.isRightHeld = true;
            break;
        case FRKey::DOWN:
            ava_pos_y += 10;
            upData.controls.isDownHeld = true;
            break;
        case FRKey::UP:
            ava_pos_y -= 10;
            upData.controls.isUpHeld = true;
            break;
        }

        ava_pos_x = ava_pos_x < 0 ? 0 : ava_pos_x;
        ava_pos_y = ava_pos_y < 0 ? 0 : ava_pos_y;

        int sx, sy;
        getScreenSize(sx, sy);

        ava_pos_x = ava_pos_x > sx ? sx : ava_pos_x;
        ava_pos_y = ava_pos_y > sy ? sy : ava_pos_y;
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
