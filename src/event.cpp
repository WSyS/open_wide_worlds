#include "event.h"


EventSetWindowBackground::EventSetWindowBackground(std::vector<Window*> *val_Windows, std::string val_id, int val_r, int val_g, int val_b, int val_a){
    Windows=val_Windows;
    id=val_id;
    r=val_r;
    g=val_g;
    b=val_b;
    a=val_a;
}


void EventSetWindowBackground::DoEvent() {

    window_set_background(Windows, id, r, g, b, a);

}


EventCloseWindow::EventCloseWindow(std::vector<Window*> *val_Windows, std::string val_id){
    Windows=val_Windows;
    id=val_id;
}


void EventCloseWindow::DoEvent() {

    window_close(Windows, id);

}


/*

Foo::Foo(int val_x, int val_y) {
    x=val_x;
    y=val_y;
}
#include <stdlib.h>
#include <iostream>

void Foo::DoEvent() {
    if ( x==12 && y==13 ){ std::cout << "Foo clicked\n"; }
}


Bar::Bar(int val_x) {
    x=val_x;
}

void Bar::DoEvent() {
    if ( x==19 ){ std::cout << "Bar clicked\n"; }
}

*/


/*
int main(){


    Event* testbutton1 = new Foo(12,13);
    Event* testbutton2 = new Bar(19);


    if ( testbutton1 != NULL)
        testbutton1->DoEvent();
    if ( testbutton2 != NULL)
        testbutton2->DoEvent();


    delete testbutton1;
    delete testbutton2;

    return 0;

}*/