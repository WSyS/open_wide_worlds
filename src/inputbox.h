

#ifndef INPUTBOX_H
#define INPUTBOX_H


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "SDL/SDL_ttf.h"

#include <string>

#define INPUTBOX_ACTIVE 0
#define INPUTBOX_INACTIVE 1
class Inputbox
{
private:

    Inputbox * selected;
    Inputbox ** checked;
    SDL_Color textColor = { 0, 0, 0 };
    TTF_Font *font = NULL;
    SDL_Rect box;
    std::string text;
    SDL_Surface *background = NULL;
    SDL_Surface *message = NULL;
    int status;
    std::string id;


public:
    Inputbox( std::string val_id, int x, int y, int width, int height, std::string default_string, uint8_t val_r,  uint8_t val_g,  uint8_t val_b, Inputbox ** val_checked);
    ~Inputbox();
    void handle_events(SDL_Event event, int offset_x = 0, int offset_y = 0);
    void show(SDL_Surface *screen);
    std::string getid();
    int getstatus();
    void changetext ( std::string Text );
};


#endif
