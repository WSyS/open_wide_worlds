#include "server.h"



int main( int argc, char* args[] )
{



    Database myDatabase("localhost", "open_wide_worlds", "game", "game");
    std::vector<Planet> Planets;
    std::vector<Ship> Ships;

    Timer database_timer;
    database_timer.start();

    while( true )
    {
        if (database_timer.get_ticks() >= REFRESH_DATABASE_EVERY_MSECOND){
            database_timer.start();





            Planets.clear();
            myDatabase.read_planets_in_universe(&myDatabase, &Planets, "*");

            for (int i=0; i<(int)Planets.size();i++){
                Planets[i].rotate();
                Planets[i].move(SCREEN_WIDTH, SCREEN_HEIGHT);
                Planets[i].calc_population();
            }

            (&myDatabase)->write_planets(&myDatabase, &Planets);





            Ships.clear();
            myDatabase.read_ships_in_universe(&myDatabase, &Ships, "*");
            for (int i=0; i<(int)Ships.size();i++){
                if (Ships[i].move()){
                    std::string fetch;

                    fetch = "UPDATE `ships` SET `x` = '";
                    fetch += NumberToString(Ships[i].getx());
                    fetch += "', `y` = '";
                    fetch += NumberToString(Ships[i].gety());
                    fetch += "' WHERE `ships`.`id` = ";
                    fetch += NumberToString(Ships[i].getid());
                    fetch += ";" ;

                    (&myDatabase)->write_in_database(&myDatabase,fetch);
                }
                Ships[i].calc_population();
            }


        }


    }



    return 0;

}
