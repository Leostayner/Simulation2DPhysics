#include <iostream>
#include "rectangle.hpp"
#include "math.h"
#include <vector>

Rectangle::Rectangle(double _m, double _wr, double _hr, double _x, double _y, double _vx, double _vy)
                    : m(_m), wr(_wr), hr(_hr), x(_x), y(_y), vx(_vx), vy(_vy){ }


std::pair<double, double> Rectangle::move(double dt, double w, double h, double mu_d){
    double new_x, new_y;

    new_x =  x + vx * dt;
    new_y =  y + vy * dt;

    double v   = sqrt(pow(vx, 2) + pow(vy, 2)); 
    double ang = atan2(vy, vx);

    double a     = - mu_d * 9.80665;    
    double new_v = v + a * dt; 

    vx = (new_v > 0)? cos(ang) * new_v: 0;
    vy = (new_v > 0)? sin(ang) * new_v: 0;

    return std::make_pair(new_x, new_y);
}