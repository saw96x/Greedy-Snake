#pragma once
#include<graphics.h>
#include<Windows.h>
#include<conio.h>
#include<ctime>
#include<vector>
#include<cstdlib>
using namespace std;
class Snake
{
public:
	Snake();
	bool check();
	void SnakeMove();
	void startup();
	void clean();
	void show();
	void UpdateWithoutInput();
	void UpdateWithInput();
	void gameover();
private:
	int High;
	int Width;
	int Background;
	int dir;
	int score;
	int speed;
	int food_x, food_y;
	vector<int> snake_x, snake_y;
};
