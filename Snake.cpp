#include"Snake.h"
Snake::Snake() {
	High = 720;
	Width = 1280;
	Background = LIGHTGRAY;
	dir = 5;
	score = 0;
	speed = 300;
	food_x = rand() % (Width-40) + 21;
	food_y = rand() % (High-40) + 21;
	snake_x.resize(4), snake_y.resize(4);
}
bool Snake::check() {
	for (int i = 0; i < snake_x.size(); i++) {
		if ((food_x >= snake_x[i] - 40 && food_x <= snake_x[i] + 40) &&
			(food_y >= snake_y[i] - 40 && food_y <= snake_y[i] + 40))
			return false;
	}
	return true;
}
void Snake::SnakeMove() {
	srand((unsigned int)(time)(NULL));
	if (food_x >= snake_x[0] - 20 &&
		food_x <= snake_x[0] + 20 &&
		food_y >= snake_y[0] - 20 &&
		food_y <= snake_y[0] + 20) {
		if (dir == 1) {
			snake_x.push_back(snake_x[snake_x.size() - 1] + 40);
			snake_y.push_back(snake_y[snake_y.size() - 1]);
		}
		else if (dir == 2) {
			snake_x.push_back(snake_x[snake_x.size() - 1]);
			snake_y.push_back(snake_y[snake_y.size() - 1] - 40);
		}
		else if (dir == 3) {
			snake_x.push_back(snake_x[snake_x.size() - 1] - 40);
			snake_y.push_back(snake_y[snake_y.size() - 1]);
		}
		else if (dir == 5) {
			snake_x.push_back(snake_x[snake_x.size() - 1]);
			snake_y.push_back(snake_y[snake_y.size() - 1] + 40);
		}
		score++;
		if (speed >= 150) {
			speed -= 5 * score;
		}
		setlinecolor(Background);
		setfillcolor(Background);
		fillcircle(food_x, food_y, 20);
		food_x = rand() % (Width - 40) + 21;
		food_y = rand() % (High - 40) + 21;
		while (!check()) {
			food_x = rand() % (Width - 40) + 21;
			food_y = rand() % (High - 40) + 21;
		}
	}
	for (int i = snake_x.size() - 1; i > 0; i--) {
		snake_x[i] = snake_x[i - 1];
		snake_y[i] = snake_y[i - 1];
	}
	if (dir == 1) {
		snake_x[0] = snake_x[1] - 40;
		snake_y[0] = snake_y[1];
	}
	else if (dir == 2) {
		snake_x[0] = snake_x[1];
		snake_y[0] = snake_y[1] + 40;
	}
	else if (dir == 3) {
		snake_x[0] = snake_x[1] + 40;
		snake_y[0] = snake_y[1];
	}
	else if (dir == 5) {
		snake_x[0] = snake_x[1];
		snake_y[0] = snake_y[1] - 40;
	}
	for (unsigned i = 1; i < snake_x.size(); i++) {
		if ((snake_x[0] >= snake_x[i] - 20 &&
			snake_x[0] <= snake_x[i] + 20 &&
			snake_y[0] >= snake_y[i] - 20 &&
			snake_y[0] <= snake_y[i] + 20) ||
			((snake_x[0] - 20 <= 0) ||
			(snake_x[0] + 20 >= 1280) ||
				(snake_y[0] - 20 <= 0) ||
				(snake_y[0] + 20 >= 720))) {
			Sleep(3000);
			exit(0);
		}
	}
}
void Snake::startup() {
	srand((unsigned int)(time)(NULL));
	initgraph(Width, High);
	setbkcolor(Background);
	cleardevice();
	for (int i = 0; i < 4; i++) {
		snake_x[i] = Width / 2 - 40 * i;
		snake_y[i] = High / 2;
	}
	BeginBatchDraw();
}
void Snake::clean() {
	setlinecolor(Background);
	setfillcolor(Background);
	for (unsigned i = 0; i < snake_x.size(); i++) {
		fillcircle(snake_x[i], snake_y[i], 20);
	}
}
void Snake::show() {
	for (unsigned i = 0; i < snake_x.size(); i++) {
		if (i == 0) {
			setfillcolor(LIGHTMAGENTA);
			fillcircle(snake_x[i], snake_y[i], 20);
		}
		else {
			setfillcolor(LIGHTRED);
			fillcircle(snake_x[i], snake_y[i], 20);
		}
	}
	FlushBatchDraw();
	setfillcolor(YELLOW);
	TCHAR s[5];
	fillcircle(food_x, food_y, 20);
	settextstyle(60, 0, _T("宋体"));
	settextcolor(RGB(25, 32, 94));
	_stprintf_s(s, 5, _T("%d"), score);
	outtextxy(430, 620, _T("Score:"));
	outtextxy(640, 620, s);

	Sleep(speed);
}
void Snake::UpdateWithoutInput() {
	SnakeMove();
}
void Snake::UpdateWithInput() {
	char input;
	if (_kbhit()) {
		input = _getch();
		if ((input == 'a' || input == '1') && dir != 3) {
			dir = 1;
			SnakeMove();
		}
		else if ((input == 's' || input == '2') && dir != 5) {
			dir = 2;
			SnakeMove();
		}
		else if ((input == 'w' || input == '5') && dir != 2) {
			dir = 5;
			SnakeMove();
		}
		else if ((input == 'd' || input == '3') && dir != 1) {
			dir = 3;
			SnakeMove();
		}
		if (input == 27) {
			input = 'n';
			while (1) {
				input = _getch();
				if (input == 27)
					break;
			}
		}
	}
}
void Snake::gameover() {
	EndBatchDraw();
	closegraph();
}
