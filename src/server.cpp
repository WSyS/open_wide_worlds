#include "server.h"



int main( int argc, char* args[] )
{
    


    Database myDatabase("localhost", "open_wide_worlds", "game", "game");
    std::vector<Planet> Planets;
    Timer database_timer;
    database_timer.start();
    int num_planets = 0;
    
    while( true )
    {
        if (database_timer.get_ticks() >= REFRESH_DATABASE_EVERY_MSECOND){
            database_timer.start();
            Planets.clear();
            num_planets = (&myDatabase)->read_planets_in_universe(&myDatabase, &Planets, "*");

            for (int i=0; i<num_planets;i++){
                Planets[i].rotate();
                Planets[i].move(SCREEN_WIDTH, SCREEN_HEIGHT);
                Planets[i].calc_population();
            }

            (&myDatabase)->write_planets(&myDatabase, &Planets);
        }


    }
    
    

    return 0;
    
}
