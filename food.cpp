#include "food.h"
#include<random>
#include <ctime>
#include <windows.h>

void goToXY2(HANDLE hOut2, int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut2, pos);
}

Food::Food(Wall &tempWall) : wall(tempWall) {
    hOut2 = GetStdHandle(STD_OUTPUT_HANDLE);
}

void Food::setFood() {
    default_random_engine e(time(nullptr));
    uniform_int_distribution<int> randomX(1, Wall::ROW - 2);
    uniform_int_distribution<int> randomY(1, Wall::COL - 2);
    while (true) {
        foodX = randomX(e);
        foodY = randomY(e);
        //只有当当前位置没有东西才放置食物
        if (wall.getWall(foodX, foodY) == ' ') {
            wall.setWall(foodX, foodY, '#');
            goToXY2(hOut2, foodY * 2, foodX);
            cout << '#';
            break;
        }
    }
}