#include <iostream>
#include <conio.h>
#include <Windows.h>
using namespace std;

// GAME MAY FLICKER WHEN RUN

bool gameOver;

//map size
const int width = 20;
const int height = 20;

int x, y, fruitX, fruitY, score;

// tail
int tailx[100], taily[100];
int length_tail;

enum direction {STOP = 0, LEFT, RIGHT, UP, DOWN};
direction dr;

void Setup() {
	gameOver = false;
	dr = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width; // creates random number where fruit is located
	fruitY = rand() % height;
	score = 0; // default score
}
void Draw() {
	system("cls"); // clear
	for (int i = 0; i < width + 2; i++) {
		cout << "#"; // Top Border
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			/*
			######
			#    # <- j == 0
			######
			*/
			if (j == 0) {
				cout << "#";
			}
			if (i == y && j == x) {
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < length_tail; k++) {
					if (tailx[k] == j && taily[k] == i) {
						cout << "o"; // tail
						print = true;
					}
				}
				if (!print) {
					cout << " "; // if tail was not printed
				}
			}
			if (j == width - 1) {
				cout << "#";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) {
		cout << "#"; // Bottom Border
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit()) { // _kbhit is if a key is pressed
		switch (_getch()) {
			case 'a': // If 'a' key is pressed
				dr = LEFT;
				break;
			case 'd': // If 'd' key is pressed
				dr = RIGHT;
				break;
			case 'w': // If 'w' key is pressed
				dr = UP;
				break;
			case 's': // If 's' key is pressed
				dr = DOWN;
				break;
			case 'x': // If 'x' key is pressed
				gameOver = true;
				break;
		}
	}
}
void Logic() {
	int prevX = tailx[0];
	int prevY = taily[0];
	int prev2X, prev2Y;
	
	tailx[0] = x;
	taily[0] = y;

	for (int i = 1; i < length_tail; i++) {
		prev2X = tailx[i];
		prev2Y = taily[i];
		tailx[i] = prevX;
		taily[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch(dr) {
		case LEFT:
			x--;
			break;
		case RIGHT:
			x++;
			break;
		case UP:
			y--;
			break;
		case DOWN:
			y++;
			break;
		default:
			break;
	}
	if (x > width || x < 0 || y > height || y < 0) {
		gameOver = true; // If snake goes out of box, gameOver = true;
	}

	for (int i = 0; i < length_tail; i++) {
		if (tailx[i] == x && taily[i] == y) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		length_tail++;
		score += 10;
		fruitX = rand() % width; // creates random number where fruit is located
		fruitY = rand() % height;
	}
}
int main() {
	Setup();
	while(!gameOver) {
		Draw();
		Input();
		Logic();
		Sleep(50); // slows speed of snake
	}
}
