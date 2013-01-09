#include "event.h"

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