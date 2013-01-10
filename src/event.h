#ifndef EVENT_H
#define EVENT_H


//#include <stdlib.h>
#include <string>
#include <vector>
#include "window.h"

class Window;

class Event
{
public:
    virtual void DoEvent() = 0;
    virtual ~Event() {};
};



class NoEvent : public Event
{
public:
    NoEvent() {};
    void DoEvent() {};
};



class EventSetWindowBackground : public Event
{
private:

    std::vector<Window*> *Windows;
    std::string id;
    int r;
    int g;
    int b;
    int a;
public:
    EventSetWindowBackground(std::vector<Window*> *val_Windows, std::string val_id, int val_r, int val_g, int val_b, int val_a);
    void DoEvent();
};



/*
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
*/


#endif