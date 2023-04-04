#include <iostream>
#include <fstream>
#include <string>
#include "Snake.h"
using namespace std;



void higherScore(string name, int score, int selection) {
    int i = 0, j = 0, k = 0, l = 0;
    string fileName[] = { "highscoreW.txt", "highscoreD.txt","highscoreC.txt" };
    int scoreInt[10];
    bool alreadyChanged = false;
    fstream new_file;
    new_file.open(fileName[(selection - 1)], ios::in);
    string scoresarr[10];
    string namesarr[10];

    // Checking whether the file is open.
    if (new_file.is_open()) {
        // cout << "File is open" << endl;
         // Read data from the file object and put it into a string.
        for (i = 0; i < 20; i++) {
            if (i < 10) {
                getline(new_file, scoresarr[i]);
                //scoresarr[i] = erase(scoresarr[i]);
            }
            if (i >= 10) {
                getline(new_file, namesarr[i - 10]);
                //namesarr[i] = erase(namesarr[i]);
            }

        }
        //cout << "after for" << endl;
        for (i = 0; i < 10; i++) {
            try {
                scoreInt[i] = stoi(scoresarr[i]);
            }
            catch (const invalid_argument& e) {
                cerr << "Error: " << e.what() << " for input string " << scoresarr[i] << endl;
                scoreInt[i] = 0;
            }

            //cout << scoreInt[i];
        }


        //shifts the data in the string if a higherscore is acheived

        for (j = 0; j < 10; j++) {
            if ((scoreInt[j] < score) && (alreadyChanged == false)) {
                //cout << "should get here" << endl;
                alreadyChanged = true;
                int temp = scoreInt[j];
                string tempN = namesarr[j];
                scoreInt[j] = score;
                namesarr[j] = name;
                for (k = 9; k > j + 1; k--) {
                    int temp2 = scoreInt[k - 1];
                    string tempN2 = namesarr[k - 1];
                    scoreInt[k] = temp2;
                    namesarr[k] = tempN2;
                }
                scoreInt[j + 1] = temp;
                namesarr[j + 1] = tempN;

            }

        }
        for (i = 0; i < 10; i++) {
            scoresarr[i] = to_string(scoreInt[i]);
            //cout << scoresarr[i];
        }

        new_file.close();
        //need to truncate file here
        ofstream ofs;
        ofs.open(fileName[(selection - 1)], std::ofstream::out | std::ofstream::trunc);
        ofs.close();



        new_file.open(fileName[(selection - 1)], ios::out);
        //cout << "does it get here" << endl;
        if (new_file.is_open()) {
            for (l = 0; l < 20; l++) {
                if (l < 10) {
                    new_file << scoreInt[l] << "\n";
                    //cout<<scoreInt[l]<<endl;
                }
                if (l >= 10) {
                    new_file << namesarr[l - 10] << "\n";
                    //cout<<namesarr[l - 10]<<endl;
                }
            }

            new_file.close();
        }
    }
}

void createFiles() {

    string filename[] = { "highscoreW.txt", "highscoreD.txt","highscoreC.txt" };
    for (int i = 0; i < 3; i++) {
        ifstream file(filename[i]);

        if (!file.good()) {
            //cout << "Cannot open file, file does not exist. Creating new file..";

            ofstream newfile(filename[i]);
            newfile << "0\n0\n0\n0\n0\n0\n0\n0\n0\n0\nname\nname\nname\nname\nname\nname\nname\nname\nname\nname\n";
            newfile.close();
            cout << "New file created!" << endl;

        }
        else {
            cout << "File already exists!" << endl;
            file.close();
        }
    }
}