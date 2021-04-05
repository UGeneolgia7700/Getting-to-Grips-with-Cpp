#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

bool isRunning;
const int width = 40;
const int height = 20;
int headX, headY, fruitX, fruitY, score = 0, tailIndex = 0, fruitFound = 0;
int tailX[100], tailY[100];

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
    int lastX = tailX[0];
    int lastY = tailY[0];
    int lastX2;
    int lastY2;
    tailX[0] = headX;
    tailY[0] = headY;

    for (int i = 1; i < tailIndex; i++) {
        lastX2 = tailX[i];
        lastY2 = tailY[i];
        tailX[i] = lastX;
        tailY[i] = lastY;
        lastX = lastX2;
        lastY = lastY2;
    }
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
    if (headX > width || headX < -1 || headY > height || headY < -1) {
        isRunning = false;
    }
    for (int i = 0; i < tailIndex; i++) {
        if (tailX[i] == headX && tailY[i] == headY) {
            isRunning = false;
        }
    }
    if (headX == fruitX && headY == fruitY) {
        score = score + 10;
        fruitFound++;
        fruitX = (rand() % (width - 1)) + 1;
        fruitY = (rand() % (height - 1)) + 1;
        tailIndex++;
    }
}
void Inputs() {
    if (_kbhit()) {
        switch (_getch()) {
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'a':
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'x':
            isRunning = false;
            break;
        default:
            break;
        }
    }

}
void Draw() {
    system("cls");
    for (int i = 0; i < width; i++) {
        cout << "#";
    }
    cout << " (w,a,s,d to move)         SCORE: " << score;
    cout << endl;
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (j == width - 1 || j == 0) {
                cout << "#";
            }
            else if (i == headY && j == headX) {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX) {
                cout << "+";
            }
            else {
                bool tailed = false;
                for (int k = 0; k < tailIndex; k++) {
                    //cout << i << " " << j << " " << tailY[k] << " " << tailX[k] << endl;
                    if (tailX[k] == j && tailY[k] == i) {
                        tailed = true;
                        cout << "o";
                    }
                }
                if (!tailed) {
                    cout << " ";
                }

            }
        }
        cout << endl;
    }
    for (int i = 0; i < width; i++) {
        cout << "I";
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
        Sleep(max(0,50-fruitFound));
    }
    cout << "\n GAME OVER!\nFinal Score: " << score;
    return 0;
}
