#pragma once

//#include <math.h>

struct rgb {
    double r;       // a fraction between 0 and 1
    double g;       // a fraction between 0 and 1
    double b;       // a fraction between 0 and 1
};

struct hsv {
    double h;       // angle in degrees
    double s;       // a fraction between 0 and 1
    double v;       // a fraction between 0 and 1
};

//stolen code yay
//https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both

hsv rgb2hsv(rgb in);

rgb hsv2rgb(hsv in);

SDL_Color rgb2sdlcolor(rgb a);

bool pointInBox(XY point, SDL_Rect rect);

XY xyAdd(XY p1, XY p2);
XY xySubtract(XY p1, XY p2);

float fxmin(float a, float b);
float fxmax(float a, float b);
float fclamp(float vmin, float b, float vmax);
double dxmin(double a, double b);
double dxmax(double a, double b);