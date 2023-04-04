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

void Draw() {

	system("CLS");

	for (int i = 0; i < width; i++) {
		//system("Color 08");
		cout << "#";
	}
	cout << endl;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				//system("Color 08");
				cout << "#";
			}
			else if (i == y && j == x) {
				//system("Color 0A");
				cout << "O";
			}
			else if (i == fruitY && j == fruitX) {
				//system("Color 04");
				cout << "F";
			}
			else {
				bool print = false;
				for (int k = 0; k < lengthTail; k++) {
					if (i == tailY[k] && j == tailX[k]) {
						//system("Color 0A");
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
		//system("Color 08");
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

	if (x < 0 || x > width || y < 0 || y > height) {
		gameOver = true;

	}

	for (int i = 0; i < lengthTail; i++) {
		if (x == tailX[i] && y == tailY[i]) {
			gameOver = true;
		}
	}

	if (x == fruitX && y == fruitY) {
		score += 1;
		fruitX = 1 + rand() % (width - 1);
		fruitY = 1 + rand() % (height - 1);
		lengthTail++;
	}
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
	cout << "Select Difficulty" << endl << "[1]: Mamba" << endl << "[2]: SideWinder" << endl << "[3]: Worm" << endl;//mamba is hard and worm is easy
	cin >> difficulty;
	return difficulty;
}

Player selection(Player player) {
	int difficulty;
	string name;
	int choice = 0;
	cin >> choice;
	system("CLS");
	switch (choice) {
	case 1:
		name = selectName();
		difficulty = selectDifficulty();
		if (difficulty == 1) {
			Mamba m;
			m.setSpeed(10);
			m.setSelection(1);
			player.setSnake(m);
			player.setName(name);
			player.setScore(0);

		}
		else if (difficulty == 2) {
			SideWinder sw;
			sw.setSpeed(40);
			sw.setSelection(2);
			player.setSnake(sw);
			player.setName(name);
			player.setScore(0);

		}
		else if (difficulty == 3) {
			Worm w;
			w.setSpeed(80);
			w.setSelection(3);
			player.setSnake(w);
			player.setName(name);
			player.setScore(0);
		}
		break;
	case 2:
		highScoreScreen();
		player.setGameOver(true);
		break;
	case 3:
		finished = true;
		break;
	default:
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

Player startScreen(Player p) {
	system("CLS");
	cout << "Welcome back to Snake!" << endl << "Select what you would like to do." << endl << "[1]: Start game" << endl << "[2]: High scores" << endl << "[3]: Exit" << endl;
	Player player = selection(p);
	return player;
}

int main() {
	srand(time(0));
	createFiles();
	Player player = startScreen();
	while (!finished) {
		Setup();
		while (!gameOver && !player.getGameOver()) {
			Draw();
			Input();
			Logic();
			Sleep(player.getSpeed());
		}
		endScreen(player);
		higherScore(player.getName(), score, player.getSelection());
		startScreen(player);
	}

	return 0;
}