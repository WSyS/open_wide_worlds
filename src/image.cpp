#include "image.h"


Image::Image(){

}


Image::Image(std::string val_id, std::string image_path , int x, int y, bool usealpha)
{
    id = val_id;
    load_image(image_path,x,y,usealpha);
}


Image::~Image()
{
    SDL_FreeSurface( imageSheet );
}


int Image::show(SDL_Surface *screen)
{
    return SDL_BlitSurface( imageSheet, NULL, screen, &box );
}


int Image::show(SDL_Surface *screen ,int x, int y)
{
    box.x = x;
    box.y = y;
    return SDL_BlitSurface( imageSheet, NULL, screen, &box );
}

int Image::show(SDL_Surface *screen ,int x, int y, int width, int height)
{
    return show(screen ,x, y, width, height, 0);

}

int Image::show(SDL_Surface *screen ,int x, int y, int width, int height, double rotation)
{
    
    int retval;
    double zoomx = (double) width / (double) imageSheet->w;
    double zoomy = (double) height / (double) imageSheet->h;
    box.x = x;
    box.y = y;


    SDL_Surface* rotatedSheet = NULL;

    rotatedSheet = rotozoomSurfaceXY(imageSheet, rotation, zoomx, zoomy, 0);

    SDL_Rect tmp;
    tmp.x = box.x + (( width / 2 ) - ( rotatedSheet->w / 2 ));
    tmp.y = box.y + (( height / 2 ) - ( rotatedSheet->h / 2 ));

    
    retval=SDL_BlitSurface( rotatedSheet, NULL, screen, &tmp );
    SDL_FreeSurface( rotatedSheet );

    return retval;

}

void Image::load_image( std::string image_path, int x, int y, bool usealpha)
{
    SDL_Surface *image = NULL;
    imageSheet = IMG_Load( image_path.c_str() );
    if (usealpha)
        SDL_SetAlpha(image, SDL_SRCALPHA, 0);


    box.x = x;
    box.y = y;
    box.w = imageSheet->w / 2;
    box.h = imageSheet->h / 2;
    path = image_path;


}

std::string Image::get_path(){

    return path;

}


std::string Image::getid(){
    return id;
}