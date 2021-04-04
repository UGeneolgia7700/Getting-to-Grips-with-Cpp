#include <iostream>
#include <conio.h>
using namespace std;

bool isRunning;
const int width = 30;
const int height = 20;
int headX, headY, fruitX, fruitY, score;

enum direction { PAUSE = 0, UP, DOWN, LEFT, RIGHT };
direction dir;

void Setup() {
    isRunning = true;
    dir = PAUSE;
    score = 0;
    headX = width / 2;
    headY = height / 2;
    fruitX = rand() % width;
    fruitY = rand() % height;
}
void Logic() {
    switch (dir) {
    case UP:
        headY--;
        break;
    case DOWN:
        headY++;
        break;
    case LEFT:
        headX--;
        break;
    case RIGHT:
        headX++;
        break;
    default:
        break;

    }
}
void Inputs() {
    if (_kbhit) {
        switch (_getch()) {
        case 'w':
            dir = UP;
        case 's':
            dir = DOWN;
        case 'a':
            dir = LEFT;
        case 'd':
            dir = RIGHT;
        case 'X':
            isRunning = false;
        }
    }

}
void Draw() {
    system("clear");
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == 0 || j == width - 1) {
                cout << "#";
            }
            else if (i == headY && j == headX) {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "+";
            }
            else {
                cout << " ";
            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << endl;
}
int main()
{
    Setup();
    while (isRunning) {
        Draw();
        Inputs();
        Logic();
    }
    return 0;
}