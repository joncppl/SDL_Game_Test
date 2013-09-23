#include "SDL/SDL.h"
#include "globals.h"
//GLOBALS
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const int SCREEN_BPP = 32;
const int FRAMES_PER_SECOND = 60;
const int CAP_FRAMES = true;
bool isFullscreen = false;

//Image on screen
SDL_Surface* screen = NULL;


//Static background image(animate it in the future ~.~)
SDL_Surface* background = NULL;


//ANIM DETAILS
//PLAYER
const int PLAYER_FRAME_WIDTH = 50;
const int PLAYER_FRAME_HEIGHT = 80;
const int PLAYER_ANIM_FRAMES = 3;
SDL_Rect CLIPS_player[PLAYER_ANIM_FRAMES];

//BULLET
const int BULLET_FRAME_WIDTH = 12;
const int BULLET_FRAME_HEIGHT = 20;

//ENEMY1
const int ENEMY1_FRAME_WIDTH = 30;
const int ENEMY1_FRAME_HEIGHT = 40;
const int ENEMY1_ANIM_FRAMES = 3;
SDL_Rect CLIPS_enemy1[ENEMY1_ANIM_FRAMES];

//SHEETS
SDL_Surface* SHEET_player = NULL;
SDL_Surface* SHEET_bullet = NULL;
SDL_Surface* SHEET_enemy1 = NULL;

int enemy1_killcount = 0;
