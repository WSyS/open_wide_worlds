#include "inputbox.h"




Inputbox::Inputbox( std::string val_id, int x, int y, int width, int height, std::string default_string, uint8_t val_r,  uint8_t val_g,  uint8_t val_b, Inputbox ** val_selected_inputbox)
{

    selected_inputbox=val_selected_inputbox;
    
    text = default_string;
    if( TTF_Init() == -1 )
    {
    }

    font = TTF_OpenFont( "font.ttf", height );

    if( font == NULL )
    {
    }

    textColor = { val_r, val_g, val_b };

    message = TTF_RenderText_Solid( font, text.c_str(), textColor );


    id=val_id;

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


    SDL_Rect fillbox = {0,0,box.w,box.h};
    Uint32 colour = SDL_MapRGBA(background->format, 128, 128, 128, 128);

    SDL_FillRect(background, &fillbox, colour);
}

Inputbox::~Inputbox()
{
    SDL_FreeSurface( background );
    SDL_FreeSurface( message );
    TTF_CloseFont( font );
    TTF_Quit();
}

void Inputbox::handle_events(SDL_Event event, int offset_x, int offset_y )
{

    int x = offset_x, y = offset_y;



    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            x = event.button.x - x;
            y = event.button.y - y;

            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                status=INPUTBOX_ACTIVE;
                changetext("clicked");
                selected_inputbox=&me;
            }
        }
    }

    return;
}

void Inputbox::show(SDL_Surface *screen)
{
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


    SDL_Surface *tmpscreen = SDL_CreateRGBSurface(SDL_SWSURFACE, box.w, box.h, screen->format->BitsPerPixel, rmask, gmask, bmask, amask);
    SDL_BlitSurface( message, NULL, tmpscreen, NULL );
    SDL_BlitSurface( tmpscreen, NULL, screen, &box );



    SDL_BlitSurface( background, NULL, screen, &box );


    SDL_FreeSurface( tmpscreen );


}


std::string Inputbox::getid(){
    return id;
}


int Inputbox::getstatus(){
    return status;
}


void Inputbox::changetext ( std::string Text ){
    
    message = TTF_RenderText_Solid( font, Text.c_str(), textColor );
}