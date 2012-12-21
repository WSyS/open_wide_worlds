#include "draw.h"


#include <iostream>

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip = NULL )
{
    //Holds offsets
    SDL_Rect offset;
    
    //Get offsets
    offset.x = x;
    offset.y = y;
    
    //Blit
    SDL_BlitSurface( source, clip, destination, &offset );
}


void stretch_apply_surface( int x, int y, int width, int height, SDL_Surface* source, SDL_Surface* destination)
{

        SDL_Rect dstrect;
    
    dstrect.x = x;
    dstrect.y = y;
    dstrect.w = width;
    dstrect.h = height;
        fprintf(stderr,"1\n");

    SDL_Surface *rotatet = rotate(source,90,0.5,0);
        fprintf(stderr,"2\n");
    
    SDL_BlitSurface( rotatet, NULL, destination, &dstrect );
        fprintf(stderr,"3\n");

    
        SDL_FreeSurface( rotatet );


}

void flip_screen(SDL_Surface *screen){
    if( SDL_Flip( screen ) == -1 )
    {
        fprintf(stderr,"Error while flip screen\n");
        exit(EXIT_FAILURE);
    }
}

/*
 S DL****_Surface *load_image( const char *path, bool usealpha){
     SDL_Surface *image = NULL;
     image = IMG_Load( path );
     if (usealpha)
         SDL_SetAlpha(image, SDL_SRCALPHA, 0);
     return image;
     
     
 }*/


//rotate image
SDL_Surface* rotate(SDL_Surface* source, double angle, double zoom, int smooth)
{
    //give initial for rotate image
    SDL_Surface* rotatefile = NULL;

    //give initial for optimizing rotate image
    SDL_Surface* optimizedrotate = NULL;

    //get rotate here
    rotatefile = rotozoomSurface(source, angle, zoom, smooth);

    //get optimizing
    optimizedrotate = SDL_DisplayFormat(rotatefile);

    //free surface
    SDL_FreeSurface( rotatefile );

    return optimizedrotate;
}