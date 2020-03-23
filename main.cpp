#include "Snake.h"
using namespace std;
int main()
{
	Snake my_snake;
	my_snake.startup();
	while (1)
	{
		my_snake.clean();
		my_snake.UpdateWithoutInput();
		my_snake.UpdateWithInput();
		my_snake.show();
	}
	my_snake.gameover();
	return 0;
}
