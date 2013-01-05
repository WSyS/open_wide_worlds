#include "window.h"


Window::Window(int x, int y, int width, int height)
{
    box.x = x;
    box.y = y;
    box.w = width;
    box.h = height;


    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    #endif
    background = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
printf("const\n");
}

Window::~Window()
{
    SDL_FreeSurface( background );
  printf("deconst\n");
  
}

int Window::is_mouse_over_window( int val_x, int val_y ){

    if( ( val_x > box.x ) && ( val_x < box.x + box.w ) && ( val_y > box.y ) && ( val_y < box.y + box.h ) ) {
        return 1;
    }
    return 0;
}

void Window::set_background(int r, int g, int b){
printf("back\n");

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = box.w;
    rect.h = box.h;
    Uint32 colour = SDL_MapRGB(background->format, r, g, b);
    SDL_FillRect(background, &rect, colour);
}

int Window::show(SDL_Surface *screen)
{
    return SDL_BlitSurface( background, NULL, screen, &box );
}