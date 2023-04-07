#include "Snake.h"

void Setup() {
	initTail();
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % (width - 1);
	fruitY = rand() % (height - 1);
	score = 0;
}

void Draw(int snakeColor) {

	system("CLS");

	for (int i = 0; i < width; i++) {
		Color(8);
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				Color (8);
				cout << "#";
			}
			else if (i == y && j == x) {
				Color(snakeColor);
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				Color(4);
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < lengthTail; k++) {
					if (i == tailY[k] && j == tailX[k]) {
						Color(snakeColor);
						cout << "o";
						print = true;
					}
				}
				if (!print)cout << " ";
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++) {
		Color(8);
		cout << "#";
	}
	cout << endl;
	cout << "Score: " << score << endl;
}
void Input() {
	if (_kbhit()) {
		switch (_getch()) {
		case 'w':
			if (dir == DOWN) {
				break;
			}
			dir = UP;
			break;
		case 'a':
			if (dir == RIGHT) {
				break;
			}
			dir = LEFT;
			break;
		case 's':
			if (dir == UP) {
				break;
			}
			dir = DOWN;
			break;
		case 'd':
			if (dir == LEFT) {
				break;
			}
			dir = RIGHT;
			break;
		default:
			break;
		}
	}
}
void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	tailX[0] = x;
	tailY[0] = y;
	int prev2X, prev2Y;

	for (int i = 1; i < lengthTail; i++) {
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}



	switch (dir) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}

	if (x <= 0 || x >= width || y <= 0 || y >= height) {
		gameOver = true;

	}

	for (int i = 0; i < lengthTail; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 1;
		fruitX = 1 + rand() % (width - 2);
		fruitY = 1 + rand() % (height - 2);
		lengthTail++;
	}
}

int getInputInt(int lowerBound, int upperBound) {
	int userInput = -1;
	bool error1 = false;
	
	do {
		cin >> userInput;
		while (!cin) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			cout << "Error. Try again: ";
			cin >> userInput;
		}
		if ((userInput <= upperBound) && (userInput >= lowerBound)) {
				error1 = true;
		}
		else {
			cout << "Error. Try again: ";
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			continue;
		}
	} while (!error1);
	return userInput;
}

string selectName() {
	string playerName = "";
	cout << "Enter player name: " << endl;
	cin >> playerName;
	system("CLS");
	return playerName;
}

int selectDifficulty() {
	int difficulty = 0;
	cout << "Select Difficulty" << endl << "[1]: Mamba(hard)" << endl << "[2]: SideWinder(normal)" << endl << "[3]: Worm(easy)" << endl;//mamba is hard and worm is easy
	//cin >> difficulty;
	difficulty = getInputInt(0,3);
	return difficulty;
}

Player selection(Player player) {
	int difficulty;
	string name;
	int choice = 0;
	bool done1 = false;
	//cin >> choice;
		choice = getInputInt(0, 3);
		system("CLS");
		switch (choice) {
		case 1:
			name = selectName();
			difficulty = selectDifficulty();
			if (difficulty == 1) {
				Mamba m;
				m.setSelection(1);
				player.setSnake(m);
				player.setName(name);
				player.setScore(0);
				m.setSnakeColor(15);
				m.setSpeed(10);

			}
			else if (difficulty == 2) {
				SideWinder sw;
				sw.setSelection(2);
				player.setSnake(sw);
				player.setName(name);
				player.setScore(0);
				sw.setSnakeColor(10);
				sw.setSpeed(30);

			}
			else if (difficulty == 3) {
				Worm w;
				w.setSelection(3);
				player.setSnake(w);
				player.setName(name);
				player.setScore(0);
				w.setSnakeColor(13);
				w.setSpeed(60);
			}
			skip = false;
			break;
		case 2:
			highScoreScreen();
			//player.setGameOver(true);
			skip = true;
			break;
		case 3:
			finished = true;
			skip = false;
			break;
		default:
			skip = false;
			break;
		}
	return player;
}

Player startScreen() {
	system("CLS");
	cout << "Welcome to Snake!" << endl << "Select what you would like to do." << endl << "[1]: Start game" << endl << "[2]: High scores" << endl << "[3]: Exit" << endl;
	Snake s;
	Player player(s, " ", 0);
	Player p = selection(player);
	return p;
}

//found on https://cplusplus.com/forum/beginner/92586/
//COLORS LIST
//1: Blue
//2: Green
//3: Cyan
//4: Red
//5: Purple
//6: Yellow (Dark)
//7: Default white
//8: Gray/Grey
//9: Bright blue
//10: Brigth green
//11: Bright cyan
//12: Bright red
//13: Pink/Magenta
//14: Yellow
//15: Bright white
//Numbers after 15 include background colors

void Color(int color)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

Player startScreen(Player p) {
	system("CLS");
	cout << "Welcome back to Snake!" << endl << "Select what you would like to do." << endl << "[1]: Start game" << endl << "[2]: High scores" << endl << "[3]: Exit" << endl;
	Player player = selection(p);
	return player;
}

int main() {
	int colorInt;
	int newSpeed;
	srand(time(0));
	createFiles();
	Player player = startScreen();
	while (!finished) {
		newSpeed = player.getSpeed();
		colorInt = player.getSnakeColor();
		Setup();
		while (!gameOver && !skip) {
			Draw(colorInt);
			Input();
			Logic();
			Sleep(newSpeed);
		}
		endScreen(player);
		higherScore(player.getName(), score, player.getSelection());
		startScreen(player);
	}

	return 0;
}
