#include "wall.h"

void Wall::initWall() {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1) {
                gameArray[i][j] = '*';
            } else {
                gameArray[i][j] = ' ';
            }
        }
    }
}

//画出整个游戏画面
void Wall::drawWall() {
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cout << gameArray[i][j] << " ";
        }
        if (i == 4) {
            cout << "w:向上";
        }
        if (i == 5) {
            cout << "s:向下";
        }
        if (i == 6) {
            cout << "a:向左";
        }
        if (i == 7) {
            cout << "d:向右";
        }
        cout << endl;
    }
}

void Wall::setWall(int x, int y, char c) {
    gameArray[x][y] = c;
}

char Wall::getWall(int x, int y) {
    return gameArray[x][y];
}

