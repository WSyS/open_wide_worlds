
#ifndef GAME_H
#define GAME_H


#define SHIPSIZE 50

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
    std::string name;
    std::string image_name;


public:
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
    std::string get_name();
    std::string get_path();
    void rotate();
    void move (int screen_width, int screen_height);
    void calc_population();
    int is_mouse_over_planet( int val_x, int val_y );
};




class Ship
{
private:

    int id;
    float x;
    float y;
    int move_x;
    int move_y;
    int shield;
    int shield_max;
    int energy;
    int hull;
    int hull_max;
    std::string loading;
    int loadcapacity;
    float movespeed;
    std::string name;

    SDL_Surface *image = NULL;

public:

    Ship( int val_id, float val_x, float val_y, int val_move_x, int val_move_y, int val_shield, int val_shield_max, int val_energy, int val_hull, int val_hull_max, std::string val_loading, int val_loadcapacity, float val_movespeed, std::string val_name);
    ~Ship();
    int getid();
    float getx();
    float gety();
    std::string get_name();
    int is_mouse_over_ship( int val_x, int val_y );
    void show(SDL_Surface *screen);

};


#endif
