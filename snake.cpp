#include <windows.h>
#include "snake.h"

void goToXY1(HANDLE hOut1, int x, int y) {
    COORD pos;//��һ�����У��ڶ�������;Ȼ�������һ�����еڶ�������
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hOut1, pos);
}

Snake::Snake(Wall &tempWall, Food &food) : wall(tempWall), food(food) {
    pHead = nullptr;
    isCircle = false;
    hOut1 = GetStdHandle(STD_OUTPUT_HANDLE);
}

//����ɾ��������
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
    //ԭ��ͷ��Ϊ�գ���Ϊ����
    if (pHead != nullptr) {
        wall.setWall(pHead->x, pHead->y, '=');

        goToXY1(hOut1, pHead->y * 2, pHead->x);//x�����2����Ϊ����һ��Ȼ�������Ǵ��㿪ʼ���
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
    addPoint(5, 3);//��һ�����У��ڶ�������
    addPoint(5, 4);
    addPoint(5, 5);
}

void Snake::delPoint() {
    //�������������Ͻڵ㣬������ɾ������
    if (pHead == nullptr || pHead->next == nullptr) {
        return;
    }
    Point *pCur = pHead->next;
    Point *pPre = pHead;
    while (pCur->next != nullptr) {
        pPre = pPre->next;
        pCur = pCur->next;
    }
    //ɾ��β�ڵ�
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
    //��β������һ���γɻ������
    if (pCur->x == x && pCur->y == y) {
        isCircle = true;
    } else {
        if (wall.getWall(x, y) == '*' || wall.getWall(x, y) == '=') {
            addPoint(x, y);
            delPoint();
            system("cls");//��������
            wall.drawWall();
            cout << "�÷֣�" << getScore() << "��" << endl;
            cout << "GAME OVER" << endl;
            return false;
        }
    }
    //�ƶ��ɹ�������
    //�Ե�ʳ���δ�Ե�ʳ��
    if (wall.getWall(x, y) == '#') {
        addPoint(x, y);
        food.setFood();
    } else {
        addPoint(x, y);
        delPoint();
        //��Ϊβ����ͷ����ظ��ˣ�����delPoint���ͷ��ɾ���ˣ�������Ҫ��������
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