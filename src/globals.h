#ifndef GLOBALS_H
#define GLOBALS_H

//GLOBALS
extern const int SCREEN_WIDTH;
extern const int SCREEN_HEIGHT;
extern const int SCREEN_BPP;
extern const int FRAMES_PER_SECOND;
extern const int CAP_FRAMES ;
extern bool isFullscreen;

//Image on screen
extern SDL_Surface* screen;


//Static background image(animate it in the future ~.~)
extern SDL_Surface* background;


//ANIM DETAILS
//PLAYER
extern const int PLAYER_FRAME_WIDTH;
extern const int PLAYER_FRAME_HEIGHT;
extern const int PLAYER_ANIM_FRAMES;
extern SDL_Rect CLIPS_player[];

//BULLET
extern const int BULLET_FRAME_WIDTH;
extern const int BULLET_FRAME_HEIGHT;

//ENEMY1
extern const int ENEMY1_FRAME_WIDTH;
extern const int ENEMY1_FRAME_HEIGHT;
extern const int ENEMY1_ANIM_FRAMES;
extern SDL_Rect CLIPS_enemy1[];

//SHEETS
extern SDL_Surface* SHEET_player;
extern SDL_Surface* SHEET_bullet;
extern SDL_Surface* SHEET_enemy1;

extern int enemy1_killcount;

#endif // GLOBALS_H
