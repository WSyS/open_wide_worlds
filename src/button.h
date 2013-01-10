

#ifndef BUTTON_H
#define BUTTON_H


#include "SDL/SDL.h"
#include "SDL/SDL_image.h"

#include "event.h"

#include <string>


#define NO_EVENT 0
#define BUTTON_PUSHED 1
#define BUTTON_RELEASED 2
#define BUTTON_MOUSEOVER 3
#define BUTTON_MOUSEOUT 4

#define BUTTON_ALIGN_TOPLEFT 0
#define BUTTON_ALIGN_CENTERCENTER 1


const int CLIP_MOUSEOVER = 0;
const int CLIP_MOUSEOUT = 1;
const int CLIP_MOUSEDOWN = 2;
const int CLIP_MOUSEUP = 3;

class Window;
class Event;

class Button
{
private:

    Event* MouseDownEvent;
    
    SDL_Rect box;
    
    SDL_Surface *buttonSheet = NULL;
    SDL_Rect clips[ 4 ];
    
    SDL_Rect* clip;

    std::string id;
    
    
public:
    Button( std::string val_id, int x, int y, int align, const char *path );
    ~Button();
    uint8_t handle_events(SDL_Event event);
    int show(SDL_Surface *screen);
    int get_x();
    int get_y();
    int get_width();
    int get_height();
    void set_xy( int x, int y );
    void set_wh( int width, int height );
    bool is_image_loaded();
    std::string getid();
    void set_MouseDownEvent(Event *event);
};


#endif
