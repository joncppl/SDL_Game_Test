#include <string>
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <stdlib.h>

SDL_Surface *load_image( std::string filename)
{


    SDL_Surface* optimizedImage = NULL;
    SDL_Surface* loadedImage = IMG_Load( filename.c_str());

    if( loadedImage !=NULL){

        optimizedImage = SDL_DisplayFormat(loadedImage);

        SDL_FreeSurface(loadedImage);

        if(optimizedImage != NULL)
        {
            SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, SDL_MapRGB(optimizedImage->format, 0, 0xFF, 0xFF));
        }
    }

    return optimizedImage;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL)
{
    SDL_Rect offset;

    offset.x=x;
    offset.y=y;

    SDL_BlitSurface( source, clip, destination, &offset);

}
