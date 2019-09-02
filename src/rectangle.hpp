#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <utility>

class Rectangle{
    
    public:
        double m, wr, hr, x, y, vx, vy;

        std::pair<double, double> move(double, double, double, double);
        Rectangle(double, double, double, double, double, double, double);
};

#endif
