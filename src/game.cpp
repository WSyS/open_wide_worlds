#include "game.h"

Planet::Planet( int val_id, int val_x, int val_y, float val_rotation, float val_rotation_speed, int val_move_x, int val_move_y, int val_move_width, int val_move_height, float val_move_angle, float val_move_speed, int val_population, int val_size, const char *val_name, const char *val_picture )
{
    //printf("make %s\n", planet_name);
    id=val_id;
    x=val_x;
    y=val_y;
    rotation=val_rotation;
    rotation_speed=val_rotation_speed;
    move_x=val_move_x;
    move_y=val_move_y;
    move_width=val_move_width;
    move_height=val_move_height;
    move_angle=val_move_angle;
    move_speed=val_move_speed;
    population=val_population;
    size=val_size;
    name=val_name;
    image_name=val_picture;
}

Planet::~Planet()
{
    //printf("destroy %s\n", name);

}

int Planet::getid(){
    return id;
}

int Planet::getx(){
    return x;
}

int Planet::gety(){
    return y;
}

float Planet::getrotation(){
    return rotation;
}


float Planet::getrotation_speed(){
    return rotation_speed;
}


float Planet::getmove_angle(){
    return move_angle;
}


int Planet::getpopulation(){
    return population;
}


int Planet::getsize(){
    return size;
}


std::string Planet::get_name(){

    return name.c_str();

}


std::string Planet::get_path(){

    return image_name.c_str();

}


void Planet::rotate (){

    rotation += rotation_speed;
    if (rotation > 360)
        rotation -= 360;
    if (rotation < 0)
        rotation += 360;
}


void Planet::move (int screen_width, int screen_height){

    float r=0;

    move_angle += move_speed;


    if ( move_width < move_height ){
        r = move_width / 2;
    }else{
        r = move_height / 2;
    }
    x = ( screen_width / 2 ) + move_x - ( size / 2 ) + ( r * sin( move_angle ) );
    y = ( screen_height / 2 ) + move_y - ( size / 2 ) + ( r * cos( move_angle ) );

    if (move_angle > 360)
        move_angle -= 360;
    if (move_angle < 0)
        move_angle += 360;
}


void Planet::calc_population(){

}


int Planet::is_mouse_over_planet( int val_x, int val_y ){

    if( ( val_x > x ) && ( val_x < x + size ) && ( val_y > y ) && ( val_y < y + size ) ) {
        return 1;
    }
    return 0;
}






Ship::Ship( int val_id, float val_x, float val_y, int val_move_x, int val_move_y, int val_shield, int val_shield_max, int val_energy, int val_hull, int val_hull_max, std::string val_loading, int val_loadcapacity, float val_movespeed, std::string val_name)
{

    Uint32 rmask, gmask, bmask, amask;
    #if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
    #else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
    #endif


    image = SDL_CreateRGBSurface(SDL_SWSURFACE, SHIPSIZE, SHIPSIZE, 32, rmask, gmask, bmask, amask);
    SDL_Rect fillbox = {0,0,SHIPSIZE,SHIPSIZE};
    Uint32 colour = SDL_MapRGBA(image->format, 0, 0, 0, 0);
    SDL_FillRect(image, &fillbox, colour);


    id = val_id;
    x = val_x;
    y = val_y;
    move_x = val_move_x;
    move_y = val_move_y;
    shield = val_shield;
    shield_max = val_shield_max;
    energy = val_energy;
    hull = val_hull;
    hull_max = val_hull_max;
    loading = val_loading;
    loadcapacity = val_loadcapacity;
    movespeed = val_movespeed;
    name = val_name;
}

Ship::~Ship()
{
    //SDL_FreeSurface( image );
}


int Ship::getid(){
    return id;
}

float Ship::getx(){
    return x;
}

float Ship::gety(){
    return y;
}


std::string Ship::get_name(){

    return name;

}


int Ship::is_mouse_over_ship( int val_x, int val_y ){

    if( ( val_x > x ) && ( val_x < x + SHIPSIZE ) && ( val_y > y ) && ( val_y < y + SHIPSIZE ) ) {
        return 1;
    }
    return 0;
}


void Ship::show(SDL_Surface *screen)
{

    Uint32 colour = SDL_MapRGBA(image->format, 0, 255, 0, 255);
    fill_circle(image,25,25,10,colour);
    SDL_Rect box = {(Sint16)x, (Sint16)y, 0, 0};
    SDL_BlitSurface( image, NULL, screen, &box );

}