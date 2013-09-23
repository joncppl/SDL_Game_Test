#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "globals.h"
#include "image_handling.h"
#include "bullet.h"
#include "enemy.h"

EnemyController::EnemyController(BulletController* BC)
{
    srand(time(NULL));

    bulletController = BC;

    SHEET_enemy1 = load_image("res/sheets/enemy1.png");

    for(int i=0; i<ENEMY1_ANIM_FRAMES; i++)
    {
        CLIPS_enemy1[i].x = ENEMY1_FRAME_WIDTH*i;
        CLIPS_enemy1[i].y = 0;
        CLIPS_enemy1[i].w = ENEMY1_FRAME_WIDTH;
        CLIPS_enemy1[i].h = ENEMY1_FRAME_HEIGHT;
    }

    Enemy enemy;
    enemy.type = 1;
    enemy.maxhealth = enemy.health = 50;
    enemy.x = SCREEN_WIDTH/2+ENEMY1_FRAME_WIDTH/2;
    enemy.y = 50;
    enemy.alive = false;
    enemy.motionTimer = 0;
    for(int i=0 ; i < 1000 ; i++)
    {
        enemy.x = rand() % SCREEN_WIDTH;
        enemy.y = rand() % SCREEN_HEIGHT / 2;
        enemies.push_back(enemy);
        enemyTimes.push_back(60+i*3*60);
    }

    animFrame = 0;
    frame = 0;
    enemyCounter = 0;

}

void EnemyController::update(SDL_Surface* screen)
{
    if(enemyTimes[enemyCounter] == frame)
        enemies[enemyCounter++].alive = true;

    for(unsigned int i=0; i < enemies.size(); i++)
    {
        if(enemies[i].alive)
        {
            switch(enemies[i].type)
            {
            case 1:
                apply_surface( enemies[i].x, enemies[i].y, SHEET_enemy1, screen, &CLIPS_enemy1[animFrame/20]);
                break;
            }

            Uint32 color = SDL_MapRGB(screen->format, (Uint8)(255-255*enemies[i].health/enemies[i].maxhealth), (Uint8)(100*enemies[i].health/enemies[i].maxhealth),0);
            SDL_Rect rect = {(Sint16)enemies[i].x,(Sint16)enemies[i].y, (Uint16)(25*enemies[i].health/enemies[i].maxhealth),8};
            SDL_FillRect(screen,&rect,color);

            rect = {(Sint16)enemies[i].x,(Sint16)enemies[i].y,25,1};
            SDL_FillRect(screen, &rect, 0xFFFFFF);
            rect = {(Sint16)enemies[i].x,(Sint16)(enemies[i].y+8),25,1};
            SDL_FillRect(screen, &rect, 0xFFFFFF);
            rect = {(Sint16)enemies[i].x,(Sint16)enemies[i].y,1,8};
            SDL_FillRect(screen, &rect, 0xFFFFFF);
            rect = {(Sint16)(enemies[i].x+25),(Sint16)enemies[i].y,1,8};
            SDL_FillRect(screen, &rect, 0xFFFFFF);

            if(enemies[i].motionTimer == 0)
            {
                enemies[i].motionPoint_x = rand() % SCREEN_WIDTH;
                enemies[i].motionPoint_y = rand() % SCREEN_HEIGHT / 2;

                enemies[i].speed = 2 + rand() % 5;

                enemies[i].motionTimer = 200 + rand() % 500;
            }

            double vel_x = enemies[i].motionPoint_x - enemies[i].x;
            double vel_y = enemies[i].motionPoint_y - enemies[i].y;

            double radius = sqrt( pow(vel_x, 2) + pow(vel_y, 2));

            vel_x /= radius;
            vel_y /= radius;

            enemies[i].x += vel_x * enemies[i].speed;
            enemies[i].y += vel_y * enemies[i].speed;

            enemies[i].motionTimer--;

            if( abs(enemies[i].x - enemies[i].motionPoint_x) < enemies[i].speed && abs(enemies[i].y - enemies[i].motionPoint_y) < enemies[i].speed )
                enemies[i].motionTimer = 0;
            if( (rand() % 10) == 1)
                bulletController->addBullet(enemies[i].x,enemies[i].y, (rand() % 7) - 3, 4, false);

        }

    }

    checkCollisions();

    checkEnemyHealth();

    frame++;
    animFrame++;
    if(animFrame >= ENEMY1_ANIM_FRAMES*20)
        animFrame = 0;
}

SDL_Rect EnemyController::getBoundBox(int id, int type)
{
    SDL_Rect box;

    box.x = enemies[id].x;
    box.y = enemies[id].y;
    switch(type)
    {
    case 1:
        box.w = ENEMY1_FRAME_WIDTH;
        box.h = ENEMY1_FRAME_HEIGHT;
        break;
    }

    return box;
}

void EnemyController::checkCollisions()
{
    for(unsigned int i=0; i < enemies.size(); i++)
    {
        for(int k =0; k < bulletController->getBulletCount(); k++)
        {
            if(enemies[i].alive && bulletController->check_collision(getBoundBox(i,enemies[i].type),bulletController->getBoundBox(k)))
            {
                if(bulletController->getBullet(k).friendly){
                    enemies[i].health--;
                    bulletController->destroyBullet(k);
                }
            }
        }
    }
}

void EnemyController::checkEnemyHealth()
{
    for(unsigned int i=0; i < enemies.size(); i++)
    {
        if(enemies[i].health <= 0 && enemies[i].alive)
        {
            enemies[i].alive = false;
            switch(enemies[i].type)
            {
            case 1:
                enemy1_killcount++;
                break;
            }
        }
    }
}
