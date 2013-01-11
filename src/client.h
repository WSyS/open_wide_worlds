
#ifndef MAIN_H
#define MAIN_H

#define RETVAL_MAIN_EXIT 0
#define RETVAL_MAIN_STARTGAME 1
#define RETVAL_MAIN_OPTIONS 2

#define CMD_QUIT 255
#define CMD_ABORT 1
#define CMD_RUN 0

#include "SDL/SDL.h"
#include "SDL/SDL_image.h"
#include "timer.h"
#include "mysql.h"
#include "inputbox.h"
#include "draw.h"
#include "button.h"
#include "image.h"
#include "game.h"
#include "font.h"
#include "window.h"
#include <string>
#include <vector>



//Screen attributes
const int SCREEN_WIDTH = 1920;
const int SCREEN_HEIGHT = 1080;
const int SCREEN_BPP = 32;
const int SCREEN_SURFACE = SDL_SWSURFACE;
//const int SCREEN_SURFACE = SDL_SWSURFACE | SDL_FULLSCREEN;


const int FRAME_EVERY_MSECOND = 100;
const int REFRESH_DATABASE_EVERY_MSECOND = 333;


uint8_t Mainmenu(SDL_Surface *screen, SDL_Event event, Timer fps);
uint8_t Optionmenu(SDL_Surface *screen, SDL_Event event, Timer fps);
uint8_t Gameloop(SDL_Surface *screen, SDL_Event event, Timer fps, Database *myDatabase);

#endif
