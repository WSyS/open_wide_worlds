
#ifndef DRAW_H
#define DRAW_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "SDL/SDL_rotozoom.h"
//#include "SDL/SDL_stretch.h"

//void apply_surface(int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip);
//void stretch_apply_surface( int x, int y, int width, int height, SDL_Surface* source, SDL_Surface* destination);
void flip_screen(SDL_Surface *screen);


//SDL_Surface *load_image( const char *path, bool usealpha );
//SDL_Surface* rotate(SDL_Surface* source, double angle, double zoom, int smooth);



void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);
#endif
