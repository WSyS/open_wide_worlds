

#ifndef WINDOW_H
#define WINDOW_H

#include "font.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>

class Window
{
private:
    SDL_Rect box;
    SDL_Surface *background;
    std::string id;
    std::vector<Font*> Fonts;

public:
    Window(std::string val_id, int x, int y, int width, int height);
    ~Window();
    int is_mouse_over_window( int val_x, int val_y );
    void set_background(int r, int g, int b, int a);
    void show(SDL_Surface *screen);
    std::string getid();
    void add_font(int val_x, int val_y, const char *Text, int val_size, uint8_t val_r,  uint8_t val_g,  uint8_t val_b);
    void remove_all_fonts();
};


void window_make(std::vector<Window*> *Windows, std::string val_id, int x, int y, int width, int height);
void window_delete(std::vector<Window*> *Windows, std::string val_id);
void window_set_background(std::vector<Window*> *Windows, std::string val_id, int r, int g, int b, int a);
#endif
