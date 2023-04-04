#pragma once
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;


extern bool firstTime;
extern bool gameOver;
extern bool finished;
extern const int height;
extern const int width;

extern int x, y, fruitX, fruitY, score;

extern int tailX[100], tailY[100], lengthTail;

enum eDirection { STOP, UP, DOWN, LEFT, RIGHT };
extern eDirection dir;

class Snake {
private:
    char head;
    char body;
    int delay;
    int selection;
    int snakeColor;
public:
    Snake() {
        head = 'O';
        body = 'o';
        delay = 40;
        selection = 1;
    }
    int getSpeed() { return delay; }
    void setSpeed(int speed) { delay = speed; }
    void setSelection(int s) { selection = s; }
    int getSelection() { return selection; }
    void setSnakeColor(int s) {snakeColor = s;}
    int getSnakeColor() { return snakeColor; }
};

class Mamba : public Snake {
public:
    Mamba() {
        setSnakeColor(15);
        setSpeed(10);
    }
    
};

class SideWinder : public Snake {
public:
    SideWinder() {
        setSnakeColor(10);
        setSpeed(30);
    }
};

class Worm : public Snake {
public:
    Worm() {
        setSnakeColor(13);
        setSpeed(60);
    }
};

class Player {
private:
    Snake snake;
    string name;
    int score;
    bool gameOver;
public:
    Player(Snake sn, string n = " ", int sc = 0, bool go = false) {
        snake = sn;
        name = n;
        score = sc;
        gameOver = go;
    }
    ~Player() { cout << "Player " << name << " defeated." << endl; }
    int getSpeed() { return snake.getSpeed(); }
    void setSnake(Snake sn) { snake = sn; }
    void setName(string n) { name = n; }
    void setScore(int sc) { score = sc; }
    string getName() { return name; }
    int getSelection() { return snake.getSelection(); }
    void setGameOver(bool go) { gameOver = go; }
    bool getGameOver() { return gameOver; }
    int getSnakeColor() { return snake.getSnakeColor(); }
    friend ostream& operator << (ostream& os, const Player&);
};

void endScreen(Player player);
void higherScore(string name, int score, int selection);
void highScoreScreen();
string erase(string s);
void createFiles();
void initTail();
void Color(int color);