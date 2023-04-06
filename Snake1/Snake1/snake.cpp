
#include <conio.h>
#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Snake.h"
using namespace std;


bool firstTime = true;
bool gameOver;
bool finished = false;
const int height = 20;
const int width = 20;

int x, y, fruitX, fruitY, score;

int tailX[100], tailY[100], lengthTail;

void initTail() {
    lengthTail = 0;
    for (int i = 0; i < 100; i++) {
        tailX[i] = -1;
        tailY[i] = -1;
    }
}


eDirection dir;

ostream& operator<<(ostream& os, const Player& p) {
    os << "Score: " << p.score;
    return os;
}

string erase(string s) {
    if (!s.empty() && s[s.size() - 1] == '\r') {
        s.erase(s.size() - 1);
    }
    return s;
}

string getWhiteSpace(string name, string score, int margins) {
    int i = 0;
    name = erase(name);
    score = erase(score);
    int lengthOfUnoccupied = margins - (name.length() + score.length());
    for (i = 0; i <= lengthOfUnoccupied; i++) {
        name += "-";
    }
    name += score;
    return name;
}

void printHighScore(string fileName, int margins = 20) {
    //cout << "in file" << endl;
    fstream new_file;
    new_file.open(fileName, ios::in);

    // Checking whether the file is open.
    if (new_file.is_open()) {

        //cout << "opened" << endl;
        string scoresarr[10];
        string namesarr[10];
        // Read data from the file object and put it into a string.
        for (int i = 0; i < 20; i++) {
            //cout<<i<<endl;
            if (i < 10) {
                getline(new_file, scoresarr[i]);
                //cout << i << scoresarr[i] << endl;
            }
            if (i >= 10) {
                getline(new_file, namesarr[i - 10]);
                //cout << i << namesarr[i - 10] << endl;
            }

        }
        string highScoreLine[10];
        //print to screen
        //cout << "thing" << endl;
        for (int j = 0; j < 10; j++) {
            highScoreLine[j] = getWhiteSpace(namesarr[j], scoresarr[j], 25);
            cout << highScoreLine[j] << "\n" << endl;

        }
        new_file.close();
    }

}


void highScoreScreen() {
    bool done = false;
    int mode = 0;
    int i = 0;
    string modeString[] = { "Mamba", "Sidewinder", "Worm" };
    string highScoresEasy = "highScoreW.txt";
    string highScoresDefualt = "highScoreD.txt";
    string highScoresHard = "highScoreC.txt";
    string optionSelection[] = { "press 0: to view highscores in Worm mode", "press 1: to view highscores in Sidewinder mode", "press 2: to view highscores in Mamba mode", "press 3: to return to main menu", "press 4: to exit program" };



    for (int i = 0; i < 4; i++) {
        cout << optionSelection[i] << endl;
    }
    while (!done) {
        //cout << "Highscores" << modeString[mode] << "\n" << endl;
        cin >> mode;
        switch (mode) {
        case 0:
            printHighScore("highscoreW.txt");
            break;
        case 1:
            printHighScore("highscoreD.txt");
            break;
        case 2:
            printHighScore("highscoreC.txt");
            break;
        case 3:
            done = true;
            break;
        default:
            break;
        }
        for (int i = 0; i < 4; i++) {
            if (i != mode) {
                cout << optionSelection[i] << endl;
            }
        }
    }
}

void endScreen(Player player) {
    system("CLS");
    player.setScore(score);
    cout << "GAME OVER" << endl;
    player.~Player();
    cout << player << endl;
    system("pause");
}

