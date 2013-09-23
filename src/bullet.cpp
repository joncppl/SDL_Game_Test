#include <vector>
#include <string>
#include "SDL/SDL.h"
#include "globals.h"
#include "image_handling.h"
#include "bullet.h"

BulletController::BulletController()
{
    SHEET_bullet = load_image("res/sheets/bullet.png");
    bulletCount = 0;
}

void BulletController::addBullet(int x, int y, int x_vel, int y_vel, bool isFriend)
{
    Bullet bullet;
    bullet.x = x;
    bullet.y = y;
    bullet.x_vel = x_vel;
    bullet.y_vel = y_vel;
    bullet.friendly = isFriend;
    bullets.push_back(bullet);
    bulletCount++;
}

void BulletController::update(SDL_Surface* screen)
{
    for(int i=0; i < bulletCount; i++)
    {
        apply_surface( bullets[i].x, bullets[i].y, SHEET_bullet, screen);
        bullets[i].x += bullets[i].x_vel;
        bullets[i].y += bullets[i].y_vel;
        if(bullets[i].x < 0-BULLET_FRAME_WIDTH || bullets[i].y < 0-BULLET_FRAME_HEIGHT || bullets[i].x > SCREEN_WIDTH || bullets[i].y > SCREEN_HEIGHT)
        {
            destroyBullet(i);
        }
    }
}

int BulletController::getBulletCount()
{
    return bulletCount;
}

Bullet BulletController::getBullet(int id)
{
    return bullets[id];
}

SDL_Rect BulletController::getBoundBox(int id)
{
    SDL_Rect box;

    box.x = bullets[id].x;
    box.y = bullets[id].y;
    box.w = BULLET_FRAME_WIDTH;
    box.h = BULLET_FRAME_HEIGHT;

    return box;
}

bool BulletController::check_collision( SDL_Rect A, SDL_Rect B)
{
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    leftA = A.x;
    rightA = A.x + A.w;
    topA = A.y;
    bottomA = A.y + A.h;

    leftB = B.x;
    rightB = B.x + B.w;
    topB = B.y;
    bottomB = B.y + B.h;

    if(bottomA <= topB)
        return false;
    if(topA >= bottomB)
        return false;
    if(rightA <= leftB)
        return false;
    if(leftA >= rightB)
        return false;
    return true;

}

void BulletController::destroyBullet(int id)
{
    bullets.erase(bullets.begin()+id);
    bulletCount--;
}
