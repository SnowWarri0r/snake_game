#ifndef SNAKE_GAME_SNAKE_H
#define SNAKE_GAME_SNAKE_H

#include<iostream>
#include "wall.h"
#include "food.h"

using namespace std;

class Snake {
private:
    struct Point {
        int x;
        int y;
        Point *next;
    };
    Point *pHead;
    Wall &wall;
    Food &food;
    bool isCircle;//蛇头与蛇尾相接时的标示
    HANDLE hOut1;
public:
    Snake(Wall &tempWall, Food &food);

    enum {
        UP = 'w',
        DOWN = 's',
        LEFT = 'a',
        RIGHT = 'd'
    };

    //初始化节点
    void initSnake();

    //销毁节点
    void destroyPoint();

    //增加节点
    void addPoint(int x, int y);

    //移动时删除节点
    void delPoint();

    //移动操作
    //返回值代表是否成功
    bool move(char key);

    //设定难度
    //获取刷屏时间
    int getSleepTime();

    //获取蛇的长度
    int countList();

    //获取分数
    int getScore();

};

#endif //SNAKE_GAME_SNAKE_H
