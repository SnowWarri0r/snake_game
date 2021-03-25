#include <iostream>
#include "wall.h"
#include "snake.h"
#include "food.h"
#include <windows.h>
#include <conio.h>

void goToXY(HANDLE hOut, int x, int y);


int main() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    bool isDead = false;

    char preKey = '\0';
    Wall wall{};
    wall.initWall();
    wall.drawWall();

    Food food(wall);
    food.setFood();
    Snake snake(wall, food);
    snake.initSnake();

    goToXY(hOut, 0, Wall::ROW);
    cout << "得分：" << snake.getScore() << endl;
    while (!isDead) {
        char key = char(_getch());//捕获输入而不需要输入回车键
        //第一次输入，输入向左移动则不会开始游戏
        if (preKey == '\0' && key == snake.LEFT) {
            continue;
        }
        do {
            if (key == snake.UP || key == snake.DOWN || key == snake.LEFT || key == snake.RIGHT) {
                if (
                        (key == snake.LEFT && preKey == snake.RIGHT) ||
                        (key == snake.UP && preKey == snake.DOWN) ||
                        (key == snake.RIGHT && preKey == snake.LEFT) ||
                        (key == snake.DOWN && preKey == snake.UP)
                        ) {
                    key = preKey;
                } else {
                    preKey = key;//不是冲突按键则更新输入
                }
                if (snake.move(key)) {
                    goToXY(hOut, 0, Wall::ROW);
                    cout << "得分：" << snake.getScore() << endl;
                    Sleep(snake.getSleepTime());
                } else {
                    isDead = true;
                    break;
                }
            } else {
                key = preKey;//强制把错误输入改成上次成功输入
            }
        } while (!_kbhit());
    }
    system("pause");
    return 0;
}

void goToXY(HANDLE hOut, int x, int y) {
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut, pos);
}