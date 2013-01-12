#include "draw.h"


#include <iostream>
/*
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


}*/

void flip_screen(SDL_Surface *screen){
    if( SDL_Flip( screen ) == -1 )
    {
        fprintf(stderr,"Error while flip screen\n");
        exit(EXIT_FAILURE);
    }
}




/*
 SDL****_Surface *load_image( const char *path, bool usealpha){
     SDL_Surface *image = NULL;
     image = IMG_Load( path );
     if (usealpha)
         SDL_SetAlpha(image, SDL_SRCALPHA, 0);
     return image;
     
     
 }*/

/*
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
}*/





void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}


void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{

    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y)
    {
        set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);

        if (x != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }

        if (y != 0)
        {
            set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }

        if (x != 0 && y != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}


void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{

    static const int BPP = 4;

    double r = (double)radius;

    for (double dy = 1; dy <= r; dy += 1.0)
    {

        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        int x = cx - dx;


        Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;

        for (; x <= cx + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
        }
    }
}