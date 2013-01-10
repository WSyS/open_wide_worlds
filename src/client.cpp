#include "client.h"




bool init(SDL_Surface **screen)
{

    if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 )
    {
        return false;
    }


    *screen = SDL_SetVideoMode( SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SCREEN_SURFACE );


    if( *screen == NULL )
    {
        return false;
    }

    SDL_WM_SetCaption( "Open Wide World", NULL );


    return true;
}


void clean_up()
{
    SDL_Quit();
}



int main( int argc, char* args[] )
{

    //The surfaces
    SDL_Surface *screen = NULL;



    //The event structure
    SDL_Event event;

    bool quit = false;


    if( init(&screen) == false )
    {
        return 1;
    }


    Timer fps;
    //Start the frame timer
    fps.start();


    Database myDatabase("localhost", "open_wide_worlds", "game", "game");


    
    while( quit == CMD_RUN )
    {
        uint8_t retval;
        retval = Mainmenu(screen, event, fps);
        if (retval == RETVAL_MAIN_EXIT)
            quit=CMD_QUIT;
        if (retval == RETVAL_MAIN_OPTIONS)
            Optionmenu(screen, event, fps);
        if (retval == RETVAL_MAIN_STARTGAME)
            if (Gameloop(screen, event, fps, &myDatabase) == CMD_QUIT)
                quit=CMD_QUIT;
    }


    clean_up();
    return 0;

}

uint8_t Mainmenu(SDL_Surface *screen, SDL_Event event, Timer fps){


    bool quit = false;

    Button Button_Play( "", ( SCREEN_WIDTH / 2 ), ( SCREEN_HEIGHT/ 2 ) - 60, BUTTON_ALIGN_TOPLEFT, "images/buttons/play.png");
    Button Button_Options( "", ( SCREEN_WIDTH / 2 ), ( SCREEN_HEIGHT/ 2 ), BUTTON_ALIGN_TOPLEFT, "images/buttons/options.png");
    Button Button_Exit( "", ( SCREEN_WIDTH / 2 ), ( SCREEN_HEIGHT/ 2 ) + 60, BUTTON_ALIGN_TOPLEFT, "images/buttons/end.png");

    Image Background( "", "images/bg_main.png" , 0, 0, false);


    while( quit == false ){
        //uint8_t *keystates = SDL_GetKeyState( NULL );
        //if( keystates[ SDLK_ESCAPE ] ) {
            //	quit = true;
            //}
            if( SDL_PollEvent( &event ) )
            {
                if (Button_Play.handle_events(event) == BUTTON_PUSHED)
                    return RETVAL_MAIN_STARTGAME;

                if (Button_Options.handle_events(event) == BUTTON_PUSHED)
                    return RETVAL_MAIN_OPTIONS;

                if (Button_Exit.handle_events(event) == BUTTON_PUSHED)
                    quit = true;

                if( event.type == SDL_QUIT )
                    quit = true;

            }

            if (fps.get_ticks() >= FRAME_EVERY_MSECOND){
                fps.start();
                Background.show(screen);
                Button_Play.show(screen);
                Button_Options.show(screen);
                Button_Exit.show(screen);
                flip_screen(screen);
            }
    }


    return RETVAL_MAIN_EXIT;
}



uint8_t Optionmenu(SDL_Surface *screen, SDL_Event event, Timer fps){


    bool quit = false;


    Button Button_Exit( "", SCREEN_WIDTH -300, SCREEN_HEIGHT - 100, BUTTON_ALIGN_TOPLEFT, "images/buttons/abort.png");

    Image Background( "", "images/bg_main.png" , 0, 0, false);


    while( quit == false ){
        uint8_t *keystates = SDL_GetKeyState( NULL );
        if( keystates[ SDLK_ESCAPE ] ) {
            quit = true;
        }
        if( SDL_PollEvent( &event ) )
        {

            if (Button_Exit.handle_events(event) == BUTTON_PUSHED)
                quit = true;

            if( event.type == SDL_QUIT )
                quit = true;

        }

        if (fps.get_ticks() >= FRAME_EVERY_MSECOND){
            fps.start();
            Background.show(screen);
            Button_Exit.show(screen);
            flip_screen(screen);
        }
    }

    return 0;

}


uint8_t Gameloop(SDL_Surface *screen, SDL_Event event, Timer fps, Database *myDatabase){

    std::vector<Planet> Planets;

    std::vector<Image> Images (2);
    Images[0].load_image("images/planets/1.png" , 0, 0, false);
    Images[1].load_image("images/suns/1.png" , 0, 0, false);

    Timer database_timer;
    database_timer.start();

    uint8_t quit = false;

    //bool submenu = false;

    int num_planets = 0;

    Image Background( "", "images/bg_stars/1.png" , 0, 0, false);

    //Font Planetinfo ( 0, 0, "" );

    std::vector<Window*> Windows;

    window_make(&Windows,"Planet",0,0,220,180);
    window_set_background(&Windows,"Planet",255,255,255,127);
    window_add_font(&Windows,"Planet","testid",10,0,"test",50,0,255,0);


    
window_add_button(&Windows,"Planet", "testbtn1", 10, 60, BUTTON_ALIGN_TOPLEFT, "images/buttons/play.png");
window_add_button(&Windows,"Planet", "testbtn2", 10, 120, BUTTON_ALIGN_TOPLEFT, "images/buttons/play.png");
window_add_button_event(&Windows,"Planet", "testbtn1", (new EventSetWindowBackground(&Windows,"Planet",255,128,255,0)));

//Button_Play.set_MouseDownEvent(new Foo(12,13));

    while( quit == CMD_RUN ){


        uint8_t *keystates = SDL_GetKeyState( NULL );
        if( keystates[ SDLK_ESCAPE ] ) {
            quit = CMD_ABORT;
        }
        while( SDL_PollEvent( &event ) )
        {

            if( event.type == SDL_QUIT )
                quit = CMD_QUIT;


            if( event.type == SDL_MOUSEBUTTONDOWN )
            {
                if( event.button.button == SDL_BUTTON_LEFT ){
                    for (int i=0; i<num_planets;i++){
                        if (Planets[i].is_mouse_over_planet ( event.button.x, event.button.y )){
                            //submenu = true;
                            //std::string tmp_text = Planets[i].get_name();
                            //Planetinfo.changetext ( tmp_text.c_str() );
                            window_set_background(&Windows,"Planet",255,255,255,0);

                        }
                    }
                }
            }
            if( event.type == SDL_MOUSEBUTTONUP ){
                //submenu = false;
                window_set_background(&Windows,"Planet",255,255,255,128);
            }

            window_handle_events(&Windows, event);

        }







        if (fps.get_ticks() >= FRAME_EVERY_MSECOND){
            fps.start();
            Background.show(screen);
            for (int i=0; i<num_planets;i++){
                for (uint j=0; j<Images.size();j++){
                    if ( Images[j].get_path() == Planets[i].get_path() ){
                        Images[j].show(screen, Planets[i].getx(), Planets[i].gety(), Planets[i].getsize(), Planets[i].getsize(),Planets[i].getrotation());
                    }
                }

            }

            /*            if (submenu == true){
             *               Planetinfo.show(screen);
        }
        */

            for (uint i=0; i<Windows.size();i++){
                //printf("showing: %d\n", i);
                Windows[i]->show(screen);
            }


            flip_screen(screen);
        }


        if (database_timer.get_ticks() >= REFRESH_DATABASE_EVERY_MSECOND){
            database_timer.start();
            Planets.clear();
            num_planets = myDatabase->read_planets_in_universe(myDatabase, &Planets, "1");
        }



        SDL_Delay(10);
    }
    
    window_delete_all(&Windows);
    return quit;


    
}