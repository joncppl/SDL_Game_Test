#include <string>
#include <sstream>
#include "SDL/SDL.h"
#include "SDL/SDL_ttf.h"
#include "globals.h"
#include "image_handling.h"
#include "osd.h"

OSD::OSD()
{
    font = TTF_OpenFont( "res/vyper.ttf", 28);
    textColor = {255, 255, 0};
    shadowColor = {50, 50, 50};
}

void OSD::update(SDL_Surface* screen)
{
    std::ostringstream str;
    str << "Kills: ";
    str << enemy1_killcount;

    surface_killcount = TTF_RenderText_Solid( font, str.str().c_str(), textColor);
    surface_killcount_shadow = TTF_RenderText_Solid( font, str.str().c_str(), shadowColor);
    apply_surface( 3, 3, surface_killcount_shadow, screen);
    apply_surface( 0, 0, surface_killcount, screen);

}
