#include "mysql.h"



Database::Database(const char *server, const char *database, const char *user, const char *pass)
{

    connect=mysql_init(NULL);

    if(!connect)
    {
        //fprintf(stderr,"MySQL Initialization Failed\n");
    }

    connect=mysql_real_connect(connect,server,user,pass,database,0,NULL,0);

    if(connect){
        //printf("Connection Succeeded\n");
    }
    else{
        //printf("Connection Failed!\n");
    }

}

Database::~Database()
{
    mysql_close(connect);
}


int Database::num_rows(const char *fetch)
{
    if(connect){

        MYSQL_RES *result;

        int i;



        mysql_query(connect, fetch);
        result = mysql_store_result(connect);

        //num_fields = mysql_num_fields(result);

        while (mysql_fetch_row(result))
        {
            i++;
        }

        mysql_free_result(result);
        return i;
    }else{
        fprintf(stderr,"Fetch error, not connected\n");
    }
    return -1;
}

void Database::fetch(const char *fetch)
{
    if(connect){

        MYSQL_RES *result;
        MYSQL_ROW row;
        MYSQL_FIELD *field;

        int num_fields;
        int i;



        mysql_query(connect, fetch);
        result = mysql_store_result(connect);

        num_fields = mysql_num_fields(result);

        while ((row = mysql_fetch_row(result)))
        {
            for(i = 0; i < num_fields; i++)
            {
                if (i == 0) {
                    while((field = mysql_fetch_field(result))) {
                        printf("%s ", field->name);
                    }
                    printf("\n");
                }
                printf("%s  ", row[i] ? row[i] : "NULL");
            }
        }
        printf("\n");

        mysql_free_result(result);

    }else{
        fprintf(stderr,"Fetch error, not connected\n");
    }
    //return 0;
}




int Database::read_planets_in_universe(Database *myDatabase, std::vector<Planet> *Planets, std::string universe)
{


    if(connect){
        std::string fetch = "SELECT `id` ,`x` , `y` ,`rotation`, `rotation_speed`, `move_x`, `move_y`, `move_width`, `move_height`, `move_angle`, `move_speed`, `population`, `size` , `name` , `picture` FROM `planets`";
        if (universe!="*")
            fetch += " WHERE  `universe` = " + universe;
        MYSQL_RES *result;
        MYSQL_ROW row;

        int i = 0;



        mysql_query(connect, fetch.c_str());
        result = mysql_store_result(connect);


        while ((row = mysql_fetch_row(result)))
        {

            i++;
            Planets->push_back ({ atoi(row[0]), atoi(row[1]), atoi(row[2]), StringToNumber<float>(row[3]), StringToNumber<float>(row[4]), atoi(row[5]), atoi(row[6]), atoi(row[7]), atoi(row[8]), StringToNumber<float>(row[9]), StringToNumber<float>(row[10]), atoi(row[11]), atoi(row[12]), row[13], row[14] });
        }


        mysql_free_result(result);

        return i;

    }
    return -1;
    //fprintf(stderr,"Fetch error, not connected\n");


}



int Database::read_ships_in_universe(Database *myDatabase, std::vector<Ship> *Ships, std::string universe)
{


    if(connect){
        std::string fetch = "SELECT `id`, `x`, `y`, `move_X`, `move_y`, `shield`, `shield_max`, `energy`, `hull`, `hull_max`, `loading`, `loadcapacity`, `movespeed`, `name` FROM `ships`";
        if (universe!="*")
            fetch += " WHERE  `universe` = " + universe;
        MYSQL_RES *result;
        MYSQL_ROW row;

        int i = 0;



        mysql_query(connect, fetch.c_str());
        result = mysql_store_result(connect);


        while ((row = mysql_fetch_row(result)))
        {

            i++;
            Ships->push_back ({ atoi(row[0]), StringToNumber<float>(row[1]), StringToNumber<float>(row[2]), atoi(row[3]),  atoi(row[4]),  atoi(row[5]),  atoi(row[6]),  atoi(row[7]),  atoi(row[8]),  atoi(row[9]), row[10], atoi(row[11]), StringToNumber<float>(row[12]), row[13]});
        }


        mysql_free_result(result);

        return i;

    }
    return -1;
    //fprintf(stderr,"Fetch error, not connected\n");


}



int Database::write_planets ( Database *myDatabase, std::vector<Planet> *Planets)
{
    if(connect){

        int retval = 0;

        for (int i =0 ; i < (int)Planets->size() ; i++){

            std::string fetch;

            fetch = "UPDATE `planets` SET `x` = '";
            fetch += NumberToString((*Planets)[i].getx());
            fetch += "', `y` = '";
            fetch += NumberToString((*Planets)[i].gety());
            fetch += "', `rotation` = '";
            fetch += NumberToString((*Planets)[i].getrotation());
            fetch += "', `move_angle` = '";
            fetch += NumberToString((*Planets)[i].getmove_angle());
            fetch += "', `population` = '";
            fetch += NumberToString((*Planets)[i].getpopulation());
            fetch += "' WHERE `planets`.`id` = ";
            fetch += NumberToString((*Planets)[i].getid());
            fetch += ";" ;
            printf("%s\n", fetch.c_str());
            //printf("planet rot %d\n",(*Planets)[i].getrotation());

            //string sql;
            //sql ="INSERT INTO md5 VALUES ('','";
            //sql +=input;
            //sql += "','tespassword')";

            if (mysql_query(connect, fetch.c_str()) == 0) {
                //cout << "Successful Insert\n";
            } else {
                retval = -2;
                break;
                //cout << "Failed Write\n";
            }

        }
        return retval;
    }
    return -1;

}



int Database::write_in_database ( Database *myDatabase, std::string fetch)
{
    if(connect){

        int retval = 0;

            //printf("%s\n", fetch.c_str());


            if (mysql_query(connect, fetch.c_str()) == 0) {
                
            } else {
                retval = -2;
                
            }

        return retval;
    }
    return -1;

}