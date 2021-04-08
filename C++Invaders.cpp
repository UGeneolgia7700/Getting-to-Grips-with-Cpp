// C++Invaders.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

const int width = 40;
const int height = 20;
bool isRunning;
int score;
int playerX = width / 2;
int lives = 10;
const int MOBMAX = 2;
const int BULLETMAX = 50;
int mobArrayX[MOBMAX];
int mobArrayY[MOBMAX];
int bulletArrayX[BULLETMAX];
int bulletArrayY[BULLETMAX];

int mobIndex, bulletIndex = 0;

void fireShot(int pos) {
	if (bulletIndex < BULLETMAX) {
		bulletArrayX[bulletIndex] = pos;
		bulletArrayY[bulletIndex] = height;
		bulletIndex++;
	}
}
void initInvaders() {
	isRunning = true;
	score = 0;
}
void draw() {
	system("cls");
	cout << "Don't let them reach Earth! Move: A,D | Shoot: L | Exit: X" << endl;
	cout << "Lives: ";
	for (int i = 0; i < lives; i++) {
		cout << "[+]";
	}
	cout << endl;
	cout << "SCORE: " << score << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (i == height - 1 && j == playerX) {
				cout << "M";
			}
			else{
				bool printed = false;
				for (int k = 0; k < bulletIndex; k++) {
					if (bulletArrayX[k] == j && bulletArrayY[k] == i) {
						cout << "o";
						printed = true;
					}
				}
				for (int k = 0; k < mobIndex; k++) {
					if (mobArrayX[k] == j && mobArrayY[k] == i) {
						cout << "V";
						printed = true;
					}
				}
				if (printed == false) {
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}
void events() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'a':
			playerX = playerX - 2;
			break;
		case 'A':
			playerX = playerX - 2;
			break;
		case 'd':
			playerX = playerX + 2;
			break;
		case 'D':
			playerX = playerX + 2;
			break;
		case 'l':
			fireShot(playerX);
			break;
		case 'L':
			fireShot(playerX);
			break;
		case 'x':
			isRunning = false;
			break;
		case 'X':
			isRunning = false;
			break;
		default:
			break;
		}
	}
}
void logic() {
	if (playerX == width+2) {
		playerX = 0;
	}
	if (playerX == -2) {
		playerX = width;
	}
	bool hit = false;
	for (int i = 0; i < mobIndex; i++) {
		mobArrayY[i]++;
		if (mobArrayY[i] > height) {
			hit = true;
			int k = 0;
			while(k < mobIndex) {
				if (k != i) {
					mobArrayY[k] = mobArrayY[i];
					mobArrayX[k] = mobArrayX[i];
				}
				else {
					mobArrayY[i] = 0;
				}
				k++;
			}
			mobIndex--;
		}
	}
	if (hit == true) {
		lives--;
		if (lives < 0) {
			isRunning = false;
		}
	}
	for (int i = 0; i < bulletIndex; i++) {
		bulletArrayY[i]--;
		if (bulletArrayY[i] < 0) {
			int k = 0;
			int newY[BULLETMAX];
			int newX[BULLETMAX];
			while (k < bulletIndex) {
				if (k != i) {
					newY[k] = bulletArrayY[i];
					newX[k] = bulletArrayX[i];
				}
				k++;
			}
			for (int l = 0; l < BULLETMAX; l++) {
				bulletArrayY[l] = newY[l];
				bulletArrayX[l] = newX[l];
			}
			bulletIndex--;
		}
	}
	if (mobIndex < MOBMAX) {
		int newX = rand() % width;
		if (newX % 2 != 0) {
			newX++;
		}
		if (newX > width) {
			newX = 20;
		}
		mobArrayX[mobIndex] = newX;
		mobArrayY[mobIndex] = 0;
		mobIndex++;
	}
	for (int i = 0; i < bulletIndex; i++) {
		for (int j = 0; j < mobIndex; j++) {
			if (bulletArrayX[i] == mobArrayX[j] && bulletArrayY[i] == mobArrayY[j]) {
				score += 10;
				int k = 0;
				int newY[BULLETMAX];
				int newX[BULLETMAX];
				while (k < bulletIndex) {
					if (k != i) {
						newY[k] = bulletArrayY[i];
						newX[k] = bulletArrayX[i];
					}
					k++;
				}
				for (int l = 0; l < BULLETMAX; l++) {
					bulletArrayY[l] = newY[l];
					bulletArrayX[l] = newX[l];
				}
				k = 0;
				int newMobY[BULLETMAX];
				int newMobX[BULLETMAX];
				while (k < bulletIndex) {
					if (k != i) {
						newMobY[k] = mobArrayY[i];
						newMobX[k] = mobArrayX[i];
					}
					k++;
				}
				for (int l = 0; l < BULLETMAX; l++) {
					mobArrayY[l] = newMobY[l];
					mobArrayX[l] = newMobX[l];
				}
				mobIndex--;
				bulletIndex--;
			}

		}
	}
}
int main() {
	initInvaders();
	while (isRunning) {
		draw();
		events();
		logic();
		Sleep(300);
	}
	return 0;
}