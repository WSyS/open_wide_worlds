#ifndef TIMER_H
#define TIMER_H

#include "SDL/SDL.h"


class Timer
{
private:
    int startTicks;
    
    int pausedTicks;
    
    bool paused;
    bool started;
    
public:
    Timer();
    
    void start();
    void stop();
    void pause();
    void unpause();
    
    int get_ticks();
    
    bool is_started();
    bool is_paused();
}; 


#endif
