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

    SDL_Rect rect;
    rect.x = 0;
    rect.y = 0;
    rect.w = box.w;
    rect.h = box.h;
    Uint32 colour = SDL_MapRGBA(background->format, r, g, b, a);
    SDL_FillRect(background, &rect, colour);
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

    SDL_Surface *windowscreen = SDL_CreateRGBSurface(SDL_SWSURFACE, box.w, box.h, 32, rmask, gmask, bmask, amask);
    for (uint i=0; i<Fonts.size();i++){
        Fonts[i]->show(windowscreen);
    }
    SDL_BlitSurface( background, NULL, screen, &box );
    SDL_BlitSurface( windowscreen, NULL, screen, &box );
    SDL_FreeSurface( windowscreen );
    
}


std::string Window::getid(){
    return id;
}


void Window::add_font(std::string id, int val_x, int val_y, const char *Text, int val_size, uint8_t val_r,  uint8_t val_g,  uint8_t val_b){
    //printf("showing x: %d\n", val_x);
    Font * f = new Font(id, val_x, val_y, Text, val_size, val_r, val_g, val_b);
    Fonts.push_back(f);
}


void Window::remove_all_fonts(){
    for (uint i=0; i<Fonts.size();i++){
        delete Fonts[i];
    }
    Fonts.clear();
}


void window_make(std::vector<Window*> *Windows, std::string id, int x, int y, int width, int height){
    Window * w = new Window(id, x, y, width, height);
    Windows->push_back(w);
}


void window_delete(std::vector<Window*> *Windows, std::string id){
    for (uint i=0; i<Windows->size();i++){
        if (id==(*Windows)[i]->getid()){
            delete (*Windows)[i];
            Windows->erase(Windows->begin()+i);
            break;
        }
    }
}


void window_set_background(std::vector<Window*> *Windows, std::string id, int r, int g, int b, int a){
    for (uint i=0; i<Windows->size();i++){
        if (id==(*Windows)[i]->getid()){
            (*Windows)[i]->set_background(r, g, b, a);
            break;
        }
    }
}