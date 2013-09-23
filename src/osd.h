#ifndef OSD_H
#define OSD_H

class OSD
{
private:
    TTF_Font *font;
    SDL_Color textColor;
    SDL_Color shadowColor;
    SDL_Surface *surface_killcount;
    SDL_Surface *surface_killcount_shadow;
public:
    OSD();
    void update(SDL_Surface *screen);
};

#endif // OSD_H
