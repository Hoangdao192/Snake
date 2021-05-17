#pragma once

#include "MainFunction.h"

class SnakeFood
{
    public:
        SnakeFood(int x_, int y_, int point_) {x = x_; y = y_; point = point_;}
        int getX() {return x; }
        int getY() {return y; }
        int getPoint() {return point; }
        void draw();
    private:
        int x, y;
        int point;
};