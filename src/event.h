#ifndef EVENT_H
#define EVENT_H


#include <stdlib.h>


class Event
{
public:
    virtual void DoEvent() = 0;
};



class Foo : public Event
{
private:
    int x;
    int y;
public:
    Foo(int val_x, int val_y);
    void DoEvent();
};



class Bar : public Event
{
private:
    int x;
public :
    Bar(int val_x);
    void DoEvent();
};



#endif