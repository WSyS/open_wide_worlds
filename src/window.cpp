#include "window.h"


Window::Window(std::string val_id, int x, int y, int width, int height)
{
    id=val_id;

    box.x = x;
    box.y = y;
    box.w = width;
    box.h = height;


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
    background = SDL_CreateRGBSurface(SDL_SWSURFACE, width, height, 32, rmask, gmask, bmask, amask);
    //printf("const\n");
}

Window::~Window()
{
    SDL_FreeSurface( background );
    remove_all_fonts();
    remove_all_buttons();
    remove_all_inputboxes();
    //printf("deconst\n");

}

int Window::is_mouse_over_window( int val_x, int val_y ){

    if( ( val_x > box.x ) && ( val_x < box.x + box.w ) && ( val_y > box.y ) && ( val_y < box.y + box.h ) ) {
        return 1;
    }
    return 0;
}


void Window::set_background(int r, int g, int b, int a){
    //printf("back\n");

    SDL_Rect fillbox = {0,0,box.w,box.h};
    Uint32 colour = SDL_MapRGBA(background->format, r, g, b, a);
    SDL_FillRect(background, &fillbox, colour);
}

void Window::show(SDL_Surface *screen)
{
    /*for (uint i=0; i<Fonts.size();i++){
     *       //printf("showing: %d\n", i);
     *       Fonts[i]->show(screen);
}
return SDL_BlitSurface( background, NULL, screen, &box );
*/
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

    SDL_Surface *windowscreen = SDL_CreateRGBSurface(SDL_SWSURFACE, box.w, box.h, screen->format->BitsPerPixel, rmask, gmask, bmask, amask);

    SDL_BlitSurface( screen, &box, windowscreen, NULL );
    SDL_BlitSurface( background, NULL, windowscreen, NULL );

    for (uint i=0; i<Fonts.size();i++){
        Fonts[i]->show(windowscreen);
    }
    for (uint i=0; i<Buttons.size();i++){
        Buttons[i]->show(windowscreen);
    }
    for (uint i=0; i<Inputboxes.size();i++){
        Inputboxes[i]->show(windowscreen);
    }

    SDL_BlitSurface( windowscreen, NULL, screen, &box );
    SDL_FreeSurface( windowscreen );

}


std::string Window::getid(){
    return id;
}


void Window::add_font(std::string id, int val_x, int val_y, const char *Text, int val_size, uint8_t val_r,  uint8_t val_g,  uint8_t val_b){
    Font * f = new Font(id, val_x, val_y, Text, val_size, val_r, val_g, val_b);
    Fonts.push_back(f);
}


void Window::remove_all_fonts(){
    for (uint i=0; i<Fonts.size();i++){
        delete Fonts[i];
    }
    Fonts.clear();
}

void window_add_font(std::vector<Window*> *Windows, std::string window_id, std::string font_id, int val_x, int val_y, const char *Text, int val_size, uint8_t val_r,  uint8_t val_g,  uint8_t val_b){
    for (uint i=0; i<Windows->size();i++){
        if (window_id==(*Windows)[i]->getid()){
            (*Windows)[i]->add_font(font_id,val_x,val_y,Text,val_size,val_r,val_g,val_b);
            break;
        }
    }
}


void window_add_button(std::vector<Window*> *Windows, std::string window_id, std::string button_id, int x, int y, int align, const char *path){
    for (uint i=0; i<Windows->size();i++){
        if (window_id==(*Windows)[i]->getid()){
            (*Windows)[i]->add_button( button_id, x, y, align, path);
            break;
        }
    }
}


void Window::add_button(std::string val_id, int x, int y, int align, const char *path){
    Button * b = new Button( val_id, x, y, align, path );
    Buttons.push_back(b);
}


void Window::remove_all_buttons(){
    for (uint i=0; i<Buttons.size();i++){
        delete Buttons[i];
    }
    Buttons.clear();
}


void window_add_inputbox(std::vector<Window*> *Windows, std::string window_id,  std::string val_id, int x, int y, int width, int height, std::string default_string, uint8_t val_r,  uint8_t val_g,  uint8_t val_b, Inputbox ** val_selected){
    for (uint i=0; i<Windows->size();i++){
        if (window_id==(*Windows)[i]->getid()){
            (*Windows)[i]->add_inputbox( val_id, x, y, width, height, default_string, val_r, val_g, val_b, val_selected);
            break;
        }
    }
}


void Window::add_inputbox( std::string val_id, int x, int y, int width, int height, std::string default_string, uint8_t val_r,  uint8_t val_g,  uint8_t val_b, Inputbox ** val_selected){
    Inputbox * i = new Inputbox( val_id, x, y, width, height, default_string, val_r, val_g, val_b, val_selected);
    Inputboxes.push_back(i);
}


void Window::remove_all_inputboxes(){
    for (uint i=0; i<Inputboxes.size();i++){
        delete Inputboxes[i];
    }
    Inputboxes.clear();
}


void Window::button_set_MouseDownEvent(std::string button_id, Event *event){
    for (uint i=0; i<Buttons.size();i++){
        if (button_id==Buttons[i]->getid()){
            Buttons[i]->set_MouseDownEvent(event);
        }
    }
}


void window_add_button_event(std::vector<Window*> *Windows, std::string window_id, std::string button_id, Event *event ){
    for (uint i=0; i<Windows->size();i++){
        if (window_id==(*Windows)[i]->getid()){
                (*Windows)[i]->button_set_MouseDownEvent(button_id,event);
        }
    }
}


void Window::handle_events(SDL_Event event){
    for (uint i=0; i<Buttons.size();i++){
        Buttons[i]->handle_events(event,box.x,box.y);
    }
    for (uint i=0; i<Inputboxes.size();i++){
        Inputboxes[i]->handle_events(event,box.x,box.y);
    }
}


void window_make(std::vector<Window*> *Windows, std::string id, int x, int y, int width, int height){
    Window * w = new Window(id, x, y, width, height);
    Windows->push_back(w);
}


void window_close(std::vector<Window*> *Windows, std::string id){
    for (uint i=0; i<Windows->size();i++){
        if (id==(*Windows)[i]->getid()){
            delete (*Windows)[i];
            Windows->erase(Windows->begin()+i);
            break;
        }
    }
}


void window_close_all(std::vector<Window*> *Windows){
    for (uint i=0; i<Windows->size();i++){
        delete (*Windows)[i];
    }
    Windows->clear();
}


void window_set_background(std::vector<Window*> *Windows, std::string id, int r, int g, int b, int a){
    for (uint i=0; i<Windows->size();i++){
        if (id==(*Windows)[i]->getid()){
            (*Windows)[i]->set_background(r, g, b, a);
            break;
        }
    }
}



void window_handle_events(std::vector<Window*> *Windows, SDL_Event event){
    for (uint i=0; i<Windows->size();i++){
        (*Windows)[i]->handle_events(event);
    }
}