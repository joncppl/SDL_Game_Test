#ifndef BULLET_H
#define BULLET_H

struct Bullet
{
    int x;
    int y;
    int x_vel;
    int y_vel;
    bool friendly;
};

class BulletController
{
private:
    std::vector<Bullet> bullets;
    int bulletCount;
public:
    BulletController();

    void addBullet(int x, int y, int x_vel, int y_vel, bool isFriend);

    void update(SDL_Surface* screen);

    int getBulletCount();

    Bullet getBullet(int id);

    SDL_Rect getBoundBox(int id);

    bool check_collision( SDL_Rect A, SDL_Rect B);

    void destroyBullet(int id);

};

#endif //BULLET_H
