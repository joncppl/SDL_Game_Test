#include <vector>
#include <string>
#include "SDL/SDL.h"
#include "image_handling.h"
#include "globals.h"

#include "bullet.h"
#include "player.h"

void Player::handle_keys(Uint8 *keystates)
{
    if(keystates[SDLK_DOWN] && keystates[SDLK_LEFT])
    {
        x -= SPEED_DIAG;
        y += SPEED_DIAG;
    }
    else if(keystates[SDLK_DOWN] && keystates[SDLK_RIGHT])
    {
        x += SPEED_DIAG;
        y += SPEED_DIAG;
    }
    else if(keystates[SDLK_UP] && keystates[SDLK_LEFT])
    {
        x -= SPEED_DIAG;
        y -= SPEED_DIAG;
    }
    else if(keystates[SDLK_UP] && keystates[SDLK_RIGHT])
    {
        x += SPEED_DIAG;
        y -= SPEED_DIAG;
    }
    else if(keystates[SDLK_DOWN])
        y += SPEED;
    else if(keystates[SDLK_UP])
        y -= SPEED;
    else if(keystates[SDLK_RIGHT])
        x += SPEED;
    else if(keystates[SDLK_LEFT])
        x -= SPEED;

    if(keystates[SDLK_z])
        fire();


    if(x < 0)
        x = 0;
    if(y < 0)
        y = 0;
    if(x > SCREEN_WIDTH - PLAYER_FRAME_WIDTH)
        x = SCREEN_WIDTH - PLAYER_FRAME_WIDTH;
    if(y > SCREEN_HEIGHT - PLAYER_FRAME_HEIGHT)
        y = SCREEN_HEIGHT - PLAYER_FRAME_HEIGHT;
}
void Player::fire()
{
    if(shootCounter == 0)
    {
        shootCounter = shootDuration;
        bulletController->addBullet(x+PLAYER_FRAME_WIDTH/2-BULLET_FRAME_WIDTH/2, y, 0, -15, 1);
    }
}

Player::Player(BulletController* BC)
{
    bulletController = BC;
    SHEET_player = load_image("res/sheets/player.png");

    for(int i=0; i<PLAYER_ANIM_FRAMES; i++)
    {
        CLIPS_player[i].x = PLAYER_FRAME_WIDTH*i;
        CLIPS_player[i].y = 0;
        CLIPS_player[i].w = PLAYER_FRAME_WIDTH;
        CLIPS_player[i].h = PLAYER_FRAME_HEIGHT;
    }

    x = (SCREEN_WIDTH - PLAYER_FRAME_WIDTH ) / 2;
    y = SCREEN_HEIGHT - PLAYER_FRAME_HEIGHT;
    frame=0;
    shootCounter = 0 ;
}
void Player::render(SDL_Surface *screen)
{
    apply_surface( x, y, SHEET_player, screen, &CLIPS_player[frame/20]);
}
void Player::update(Uint8 *keystates)
{
    frame++;
    if(frame>=PLAYER_ANIM_FRAMES*20)
        frame=0;
    handle_keys(keystates);

    if(shootCounter > 0)
        shootCounter--;

}
