#include "draw.h"


#include <iostream>


void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
    Uint8 *target_pixel = (Uint8 *)surface->pixels + y * surface->pitch + x * 4;
    *(Uint32 *)target_pixel = pixel;
}


void draw_circle(SDL_Surface *surface, int n_cx, int n_cy, int radius, Uint32 pixel)
{

    double error = (double)-radius;
    double x = (double)radius -0.5;
    double y = (double)0.5;
    double cx = n_cx - 0.5;
    double cy = n_cy - 0.5;

    while (x >= y)
    {
        set_pixel(surface, (int)(cx + x), (int)(cy + y), pixel);
        set_pixel(surface, (int)(cx + y), (int)(cy + x), pixel);

        if (x != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy + y), pixel);
            set_pixel(surface, (int)(cx + y), (int)(cy - x), pixel);
        }

        if (y != 0)
        {
            set_pixel(surface, (int)(cx + x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy + x), pixel);
        }

        if (x != 0 && y != 0)
        {
            set_pixel(surface, (int)(cx - x), (int)(cy - y), pixel);
            set_pixel(surface, (int)(cx - y), (int)(cy - x), pixel);
        }

        error += y;
        ++y;
        error += y;

        if (error >= 0)
        {
            --x;
            error -= x;
            error -= x;
        }
    }
}


void fill_circle(SDL_Surface *surface, int cx, int cy, int radius, Uint32 pixel)
{

    static const int BPP = 4;

    double r = (double)radius;

    for (double dy = 1; dy <= r; dy += 1.0)
    {

        double dx = floor(sqrt((2.0 * r * dy) - (dy * dy)));
        int x = cx - dx;


        Uint8 *target_pixel_a = (Uint8 *)surface->pixels + ((int)(cy + r - dy)) * surface->pitch + x * BPP;
        Uint8 *target_pixel_b = (Uint8 *)surface->pixels + ((int)(cy - r + dy)) * surface->pitch + x * BPP;

        for (; x <= cx + dx; x++)
        {
            *(Uint32 *)target_pixel_a = pixel;
            *(Uint32 *)target_pixel_b = pixel;
            target_pixel_a += BPP;
            target_pixel_b += BPP;
        }
    }
}