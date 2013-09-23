#ifndef ENEMY_H
#define ENEMY_H

#include <stdlib.h>
#include <time.h>
#include <math.h>
struct Enemy
{
    int type;
    int maxhealth;
    int health;
    double x,y;
    bool alive;
    double motionPoint_x;
    double motionPoint_y;
    int motionTimer;
    double speed;
};


class EnemyController
{
private:
    int frame;
    int animFrame;
    int enemyCounter;
    std::vector<Enemy> enemies;
    std::vector<int> enemyTimes;
    BulletController* bulletController;
public:
    EnemyController(BulletController* BC);

    void update(SDL_Surface* screen);

    SDL_Rect getBoundBox(int id, int type);

    void checkCollisions();

    void checkEnemyHealth();
};

#endif // ENEMY_H
