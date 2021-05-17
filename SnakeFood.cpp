#include "SnakeFood.h"

void SnakeFood::draw()
{
    gotoXY(x, y);
    cout << FOOD_COLOR_TEXT.c_str() << "O" << "\033[0m";
}