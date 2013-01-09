
#ifndef FONT_H
#define FONT_H


#include "SDL/SDL_ttf.h"
#include <string>


class Font
{
private:

    SDL_Color textColor = { 0, 0, 0 };
    TTF_Font *font = NULL;
    SDL_Surface *message = NULL;
    int x;
    int y;

public:

    Font( int var_x, int var_y, const char *Text, int val_size, uint8_t val_r,  uint8_t val_g,  uint8_t val_b );
    ~Font();
    void changetext ( const char *Text );
    int show(SDL_Surface *screen);
};

#endif
