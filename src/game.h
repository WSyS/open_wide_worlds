
#ifndef GAME_H
#define GAME_H

#include "draw.h"
#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include <string>

class Planet
{
private:

    int id;
    int x;
    int y;
    float rotation;
    float rotation_speed;
    int move_x;
    int move_y;
    int move_width;
    int move_height;
    float move_angle;
    float move_speed;
    int population;
    int size;
    const char *name;
    const char *image_name;


public:
    //Planet();
    Planet( int val_id, int val_x, int val_y, float val_rotation, float val_rotation_speed, int val_move_x, int val_move_y, int val_move_width, int val_move_height, float val_move_angle, float val_move_speed, int val_population, int val_size, const char *val_name, const char *val_picture );
    ~Planet();
    int getid();
    int getx();
    int gety();
    float getrotation();
    float getrotation_speed();
    float getmove_angle();
    int getpopulation();
    int getsize();
    void show(SDL_Surface *screen);
    std::string get_name();
    std::string get_path();
    void rotate();
    void move (int screen_width, int screen_height);
    void calc_population();
    int is_mouse_over_planet( int val_x, int val_y );
};


//int get_planets_in_universe( Database *myDatabase );



#endif
