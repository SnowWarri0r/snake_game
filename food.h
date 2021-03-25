#ifndef SNAKE_GAME_FOOD_H
#define SNAKE_GAME_FOOD_H

#include<iostream>
#include <windows.h>
#include "wall.h"

using namespace std;

class Food {
public:

    explicit Food(Wall &tempWall);

    void setFood();

private:
    int foodX{};
    int foodY{};
    Wall &wall;
    HANDLE hOut2;
};


#endif //SNAKE_GAME_FOOD_H
