#ifndef SNAKE_GAME_WALL_H
#define SNAKE_GAME_WALL_H

#include <iostream>

using namespace std;

class Wall {
public:
    enum {
        ROW = 26,//行数
        COL = 26//列数
    };

    //初始化墙壁
    void initWall();

    //画出墙壁
    void drawWall();

    //用于设置屏幕上的内容，食物和蛇的身体
    void setWall(int x, int y, char c);

    //获取当前位置的符号，在设置食物和蛇吃掉食物的蛇身要用
    char getWall(int x, int y);

private:
    char gameArray[ROW][COL];
};

#endif //SNAKE_GAME_WALL_H
