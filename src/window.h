

#ifndef WINDOW_H
#define WINDOW_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

class Window
{
private:
    SDL_Rect box;
    SDL_Surface *background;

public:
    Window(int x, int y, int width, int height);
    ~Window();
    int is_mouse_over_window( int val_x, int val_y );
    void set_background(int r, int g, int b);
    int show(SDL_Surface *screen);
};


#endif
