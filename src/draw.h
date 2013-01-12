
#ifndef DRAW_H
#define DRAW_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

 #include <cmath>

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel);
void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel);
void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel);
#endif
