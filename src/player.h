#ifndef PLAYER_H
#define PLAYER_H
class Player
{
private:
    static const int SPEED = 10;
    static const int SPEED_DIAG = 0.70710678118654752*SPEED;
    BulletController* bulletController;


    int frame;
    int shootCounter;
    static const int shootDuration = 2;

    //handle movement
    void handle_keys(Uint8 *keystates);
    void fire();
public:
    int x,y;

    Player(BulletController* BC);

    void render(SDL_Surface *screen);

    void update(Uint8 *keystates);

};

#endif // PLAYER_H
