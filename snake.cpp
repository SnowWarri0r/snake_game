#include <windows.h>
#include "snake.h"

void goToXY1(HANDLE hOut1, int x, int y) {
    COORD pos;//第一个是列，第二个是行;然而数组第一个是行第二个是列
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut1, pos);
}

Snake::Snake(Wall &tempWall, Food &food) : wall(tempWall), food(food) {
    pHead = nullptr;
    isCircle = false;
    hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);
}

//用于删除整条蛇
void Snake::destroyPoint() {
    Point *pCur;
    while (pHead != nullptr) {
        pCur = pHead->next;
        delete pHead;

        pHead = pCur;
    }
}

void Snake::addPoint(int x, int y) {
    auto *newPoint = new Point;
    newPoint->x = x;
    newPoint->y = y;
    newPoint->next = nullptr;
    //原来头不为空，改为身体
    if (pHead != nullptr) {
        wall.setWall(pHead->x, pHead->y, '=');

        goToXY1(hOut1, pHead->y * 2, pHead->x);//x坐标乘2是因为空了一格，然后坐标是从零开始算的
        cout << "=";
    }
    newPoint->next = pHead;
    pHead = newPoint;
    wall.setWall(pHead->x, pHead->y, '@');
    goToXY1(hOut1, pHead->y * 2, pHead->x);
    cout << "@";
}

void Snake::initSnake() {
    destroyPoint();
    addPoint(5, 3);//第一个是行，第二个是列
    addPoint(5, 4);
    addPoint(5, 5);
}

void Snake::delPoint() {
    //两个及两个以上节点，可以做删除操作
    if (pHead == nullptr || pHead->next == nullptr) {
        return;
    }
    Point *pCur = pHead->next;
    Point *pPre = pHead;
    while (pCur->next != nullptr) {
        pPre = pPre->next;
        pCur = pCur->next;
    }
    //删除尾节点
    wall.setWall(pCur->x, pCur->y, ' ');
    goToXY1(hOut1, pCur->y * 2, pCur->x);
    cout << " ";
    delete pCur;

    pPre->next = nullptr;
}

bool Snake::move(char key) {
    int x = pHead->x;
    int y = pHead->y;

    switch (key) {
        case UP:
            x--;
            break;
        case DOWN:
            x++;
            break;
        case LEFT:
            y--;
            break;
        case RIGHT:
            y++;
            break;
        default:
            break;
    }
    Point *pCur = pHead->next;
    Point *pPre = pHead;

    while (pCur->next != nullptr) {
        pPre = pPre->next;
        pCur = pCur->next;
    }
    //和尾巴碰到一起形成环的情况
    if (pCur->x == x && pCur->y == y) {
        isCircle = true;
    } else {
        if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=') {
            addPoint(x, y);
            delPoint();
            system("cls");//清屏操作
            wall.drawWall();
            cout << "得分：" << getScore() << "分" << endl;
            cout << "GAME OVER" << endl;
            return false;
        }
    }
    //移动成功分两种
    //吃到食物和未吃到食物
    if (wall.getWall(x, y) == '#') {
        addPoint(x, y);
        food.setFood();
    } else {
        addPoint(x, y);
        delPoint();
        //因为尾结点和头结点重复了，所以delPoint会把头给删掉了，所以需要重新设置
        if (isCircle) {
            wall.setWall(x, y, '@');
            goToXY1(hOut1, y * 2, x);
            cout << "@";
        }
    }

    return true;
}

int Snake::getSleepTime() {
    int sleepTime;
    int size = countList();
    if (size < 5) {
        sleepTime = 300;
    } else if (size >= 5 && size <= 10) {
        sleepTime = 200;
    } else {
        sleepTime = 100;
    }
    return sleepTime;
}

int Snake::countList() {
    int size = 0;
    Point *curPoint = pHead;
    while (curPoint != nullptr) {
        size++;
        curPoint = curPoint->next;
    }
    return size;
}

int Snake::getScore() {
    int size = countList();
    int score = (size - 3) * 100;
    return score;
}