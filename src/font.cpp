#include "font.h"



Font::Font( int var_x, int var_y, const char *Text )
{
    if( TTF_Init() == -1 )
    {
    }

    font = TTF_OpenFont( "font.ttf", 50 );

    if( font == NULL )
    {
    }

    message = TTF_RenderText_Solid( font, Text, textColor );

    x = var_x;
    y = var_y;
    
}

Font::~Font()
{
    SDL_FreeSurface( message );
    TTF_CloseFont( font );
    TTF_Quit();
}


void Font::changetext ( const char *Text ){
        message = TTF_RenderText_Solid( font, Text, textColor );
}

int Font::show(SDL_Surface *screen)
{

    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    return SDL_BlitSurface( message, NULL, screen, &offset );
}

