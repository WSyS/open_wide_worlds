#ifndef IMAGE_H
#define IMAGE_H

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_rotozoom.h"
#include <string>


class Image
{
private:
    SDL_Rect box;
    SDL_Surface *imageSheet = NULL;
    std::string path;

    std::string id;
    
public:
    Image();
    Image(std::string val_id, std::string image_path, int x, int y, bool usealpha);
    ~Image();
    
    int show(SDL_Surface *screen);
    int show(SDL_Surface *screen, int x, int y);
    int show(SDL_Surface *screen, int x, int y, int width, int height);
    int show(SDL_Surface *screen, int x, int y, int width, int height, double rotation);
    std::string get_path();
    void load_image( std::string image_path, int x, int y, bool usealpha);
    std::string getid();
};


#endif
