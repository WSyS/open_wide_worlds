#ifndef MYSQL_H
#define MYSQL_H

#include <mysql/mysql.h>
#include <string>
#include <vector>
#include "game.h"
#include "string.h"

class Planet;
class Ship;

class Database
{
private:

    MYSQL *connect;

public:


    Database(const char *server, const char *database, const char *user, const char *pass);
    ~Database();
    int num_rows(const char *fetch);
    void fetch(const char *fetch);
    int read_planets_in_universe(Database *myDatabase, std::vector<Planet> *Planets, std::string universe);
    int read_ships_in_universe(Database *myDatabase, std::vector<Ship> *Shipss, std::string universe);
    int write_planets (Database *myDatabase, std::vector<Planet> *Planets);
    int write_in_database ( Database *myDatabase, std::string fetch);
};





#endif

