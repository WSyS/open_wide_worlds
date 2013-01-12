

#ifndef WINDOW_H
#define WINDOW_H

#include "font.h"
#include "button.h"
#include "event.h"
#include "inputbox.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>
#include <vector>

class Button;
class Event;

class Window
{
private:
    SDL_Rect box;
    SDL_Surface *background;
    std::string id;
    std::vector<Font*> Fonts;
    std::vector<Button*> Buttons;
    std::vector<Inputbox*> Inputboxes;

public:
    Window(std::string val_id, int x, int y, int width, int height);
    ~Window();
    int is_mouse_over_window( int val_x, int val_y );
    void set_background(int r, int g, int b, int a);
    void show(SDL_Surface *screen);
    std::string getid();
    void add_font(std::string id, int val_x, int val_y, const char *Text, int val_size, uint8_t val_r,  uint8_t val_g,  uint8_t val_b);
    void remove_all_fonts();
    void add_button(std::string val_id, int x, int y, int align, const char *path);
    void remove_all_buttons();
    void add_inputbox( std::string val_id, int x, int y, int width, int height, std::string default_string, uint8_t val_r,  uint8_t val_g,  uint8_t val_b, Inputbox ** val_selected);
    void remove_all_inputboxes();
    void handle_events(SDL_Event event);
    void button_set_MouseDownEvent(std::string button_id, Event *event);
    
};

void window_add_font(std::vector<Window*> *Windows, std::string window_id, std::string font_id, int val_x, int val_y, const char *Text, int val_size, uint8_t val_r,  uint8_t val_g,  uint8_t val_b);
void window_add_button(std::vector<Window*> *Windows, std::string window_id, std::string button_id, int x, int y, int align, const char *path);
void window_add_button_event(std::vector<Window*> *Windows, std::string window_id, std::string val_id, Event *event );
void window_add_inputbox(std::vector<Window*> *Windows, std::string window_id, std::string button_id, int x, int y, int width, int height, std::string default_string, uint8_t val_r,  uint8_t val_g,  uint8_t val_b, Inputbox ** val_selected);
void window_make(std::vector<Window*> *Windows, std::string val_id, int x, int y, int width, int height);
void window_close(std::vector<Window*> *Windows, std::string val_id);
void window_close_all(std::vector<Window*> *Windows);
void window_set_background(std::vector<Window*> *Windows, std::string val_id, int r, int g, int b, int a);
void window_handle_events(std::vector<Window*> *Windows, SDL_Event event);
#endif
