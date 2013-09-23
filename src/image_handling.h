#ifndef IMAGE_HANDLING_H
#define IMAGE_HANDLING_H

SDL_Surface *load_image( std::string filename);

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL);

#endif // IMAGE_HANDLING_H
