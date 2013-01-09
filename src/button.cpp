#include "button.h"




Button::Button( std::string val_id, int x, int y, int align, const char *path )
{

    id = val_id;
    
    buttonSheet = IMG_Load( path );
    if( buttonSheet == NULL )
    {
        return;
    }

    SDL_SetAlpha(buttonSheet, SDL_SRCALPHA, 0);

    switch ( align ){
        case BUTTON_ALIGN_CENTERCENTER:
            box.x = x;
            box.y = y;
            break;
        case BUTTON_ALIGN_TOPLEFT:
        default:
            box.x = x;
            box.y = y;
    }
    box.w = buttonSheet->w / 2;
    box.h = buttonSheet->h / 2;


    clips[ CLIP_MOUSEOVER ].x = 0;
    clips[ CLIP_MOUSEOVER ].y = 0;
    clips[ CLIP_MOUSEOVER ].w = buttonSheet->w / 2;
    clips[ CLIP_MOUSEOVER ].h = buttonSheet->h / 2;

    clips[ CLIP_MOUSEOUT ].x = buttonSheet->w / 2;
    clips[ CLIP_MOUSEOUT ].y = 0;
    clips[ CLIP_MOUSEOUT ].w = buttonSheet->w / 2;
    clips[ CLIP_MOUSEOUT ].h = buttonSheet->h / 2;

    clips[ CLIP_MOUSEDOWN ].x = 0;
    clips[ CLIP_MOUSEDOWN ].y = buttonSheet->h / 2;
    clips[ CLIP_MOUSEDOWN ].w = buttonSheet->w / 2;
    clips[ CLIP_MOUSEDOWN ].h = buttonSheet->h / 2;

    clips[ CLIP_MOUSEUP ].x = buttonSheet->w / 2;
    clips[ CLIP_MOUSEUP ].y = buttonSheet->h / 2;
    clips[ CLIP_MOUSEUP ].w = buttonSheet->w / 2;
    clips[ CLIP_MOUSEUP ].h = buttonSheet->h / 2;


    clip = &clips[ CLIP_MOUSEOUT ];
}

Button::~Button()
{
    SDL_FreeSurface( buttonSheet );
}

uint8_t Button::handle_events(SDL_Event event)
{
    int x = 0, y = 0;

    if( event.type == SDL_MOUSEMOTION )
    {
        x = event.motion.x;
        y = event.motion.y;

        if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
        {
            clip = &clips[ CLIP_MOUSEOVER ];
            return BUTTON_MOUSEOVER;
        }
        else
        {
            clip = &clips[ CLIP_MOUSEOUT ];
            return BUTTON_MOUSEOUT;
        }
    }

    if( event.type == SDL_MOUSEBUTTONDOWN )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            x = event.button.x;
            y = event.button.y;

            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                clip = &clips[ CLIP_MOUSEDOWN ];
                return BUTTON_PUSHED;
            }
        }
    }

    if( event.type == SDL_MOUSEBUTTONUP )
    {
        if( event.button.button == SDL_BUTTON_LEFT )
        {
            x = event.button.x;
            y = event.button.y;

            if( ( x > box.x ) && ( x < box.x + box.w ) && ( y > box.y ) && ( y < box.y + box.h ) )
            {
                clip = &clips[ CLIP_MOUSEUP ];
                return BUTTON_RELEASED;
            }
        }
    }
    return NO_EVENT;
}

int Button::show(SDL_Surface *screen)
{
        return SDL_BlitSurface( buttonSheet, clip, screen, &box );
}


int Button::get_x(){
    return box.x;
}


int Button::get_y(){
    return box.y;
}


int Button::get_width(){
    return box.w;
}


int Button::get_height(){
    return box.h;
}


void Button::set_xy( int x, int y ){
    box.x = x;
    box.y = y;
}


void Button::set_wh( int width, int height ){
    box.w = width;
    box.h = height;
}


bool Button::is_image_loaded(){

    if( buttonSheet == NULL )
    {
        return false;
    }
    return true;
}


std::string Button::getid(){
    return id;
}