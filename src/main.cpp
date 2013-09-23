#include <string>
#include <vector>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include "globals.h"
#include "timer.h"
#include "image_handling.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
#include "osd.h"

#include <iostream>

//Symbolic constants


//Event
SDL_Event event;



bool load_background()
{

    //load background image
    background = load_image("res/background.png");

    //Ensure it loaded successfully
    if(background == NULL)
        return false;

    return true;
}

bool init()
{
    //Initialize SDL
    if(SDL_Init(SDL_INIT_EVERYTHING) == -1)
        return false;

    //Set Video Out
    if(isFullscreen)
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE|SDL_FULLSCREEN);
    else
        screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);

    //Confirm SDL_Surface screen is pointing to something
    if(screen==NULL)
        return false;

    //Set Caption to "SDL Game Test"
    SDL_WM_SetCaption("SDL Scrolling Shooter", NULL);

    TTF_Init();

    return true;
}

int main(int argc, char* argv[])
{
    //Quit Trigger
    bool quit = false;

    //fps stuff;
    int frame = 0;
    Timer fps;

    //Initiate SDL and such
    if(!init())
        return 1;

    //Load background
    if(!load_background())
        return 2;
    //Load in other images
    BulletController* bulletController = new BulletController();
    EnemyController* enemyController = new EnemyController(bulletController);
    Player player(bulletController);
    OSD osd;



    //Put all image loading into one function?
    //Definitely Going to use sprite sheets

    //The loop :D
    while(!quit)
    {
        //start timing fps
        fps.start();

        //Check for events
        if(SDL_PollEvent(&event))
        {
            //Quit when X is pressed
            if(event.type == SDL_QUIT)
                quit = true;
        }
        //Get keystates
        Uint8 *keystates = SDL_GetKeyState( NULL );
        if(keystates[SDLK_ESCAPE]){
            quit = true;
        }
        if((keystates[SDLK_RALT] && keystates[SDLK_RETURN]) || keystates[SDLK_F11]){
            if(isFullscreen)
                screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
            else
                screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE|SDL_FULLSCREEN);
            isFullscreen = !isFullscreen;
        }


        //update
        player.update(keystates);


        //render
        apply_surface( 0, 0, background, screen);
        player.render(screen);
        bulletController->update(screen);
        enemyController->update(screen);
        osd.update(screen);



        //Refresh the SCREEN
        if(SDL_Flip(screen) == -1)
            return 9999;


        frame++;
        if( (CAP_FRAMES) && (fps.get_ticks() < 1000 / FRAMES_PER_SECOND))
        {
            SDL_Delay((1000 / FRAMES_PER_SECOND) - fps.get_ticks());
        }
    }

    return 0;
}
