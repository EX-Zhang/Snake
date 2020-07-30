#include "game.h"

game::game()
{
	this->rows = 30;
	this->cols = 100;

	map new_map(this->rows, this->cols);
	this->game_map = new_map;

	int snake_x = get_rand(this->cols);
	int snake_y = get_rand(this->rows);

	while (true) {

		if (!this->game_map.is_edge(snake_x, snake_y) && !this->game_map.is_edge(snake_x - 1, snake_y) && !this->game_map.is_edge(snake_x - 2, snake_y)) {
			break;
		}

		snake_x = get_rand(this->cols); 
		snake_y = get_rand(this->rows); 
	}

	snake new_snake(snake_x, snake_y);
	this->player_snake = new_snake;

	this->score = 0;
	
	this->food[0] = 0;
	this->food[1] = 0;
}

void game::print_game()
{

	for (int i = 0; i < this->cols; i++) {
		for (int j = 0; j < this->rows; j++) {

			setPos(i, j);

			if (this->game_map.is_edge(i, j)) {
				printf("A");
			}
			else if (this->player_snake.pos_has_node(i, j)) {
				printf("S");
			}
			else if (this->is_food(i, j)) {
				printf("F");
			}
			else {
				printf(" ");
			}

		}
	}

}

void game::generate_food()
{

	int cur_x = this->food[0];
	int cur_y = this->food[1];

	int food_x = get_rand(this->cols);
	int food_y = get_rand(this->rows);

	while (true) {

		if (food_x != cur_x && food_y != cur_y && !this->game_map.is_edge(food_x, food_y) && !this->player_snake.pos_has_node(food_x, food_y)) {
			break;
		}

		food_x = get_rand(this->cols); 
		food_y = get_rand(this->rows);

	}

	this->food[0] = food_x;
	this->food[1] = food_y;
}

bool game::is_food()
{
	int x, y;

	this->player_snake.next_head_position(&x, &y);

	return x == this->food[0] && y == this->food[1];
}

bool game::is_food(int x, int y)
{
	return x == this->food[0] && y == this->food[1];
}

bool game::is_game_end()
{

	int x, y;

	this->player_snake.get_cur_position(&x, &y);

	return this->player_snake.hit_self() || this->game_map.is_edge(x, y);

}

void game::game_start()
{
	this->generate_food();

	char str[255];
	sprintf(str, "mode con cols=%d lines=%d", this->cols, this->rows);
	system(str);

	setPos(cols / 2 - 10, rows / 2);
	printf("Press ENTER to start\n");

	getchar();

	this->print_game();
}

void game::game_circle()
{
	int n = 0;

	while (true) {

		

		if (n == 100000) {

			this->print_game();

			if (GetAsyncKeyState(VK_UP)) {
				this->player_snake.change_direction(UP);
			}
			else if (GetAsyncKeyState(VK_DOWN)) {
				this->player_snake.change_direction(DOWN);
			}
			else if (GetAsyncKeyState(VK_LEFT)) {
				this->player_snake.change_direction(LEFT);
			}
			else if (GetAsyncKeyState(VK_RIGHT)) {
				this->player_snake.change_direction(RIGHT);
			}

			int x, y;

			this->player_snake.get_cur_position(&x, &y);

			if (is_food(x,y)) {
				this->player_snake.add();
				generate_food();
				this->score++;
			}
			else {
				this->player_snake.move();
			}



			n = 0;
		}

		if (this->is_game_end()) {
			this->print_game();
			break;
		}
		n++;

	}

}

void game::game_end()
{

	this->clean_screen();

	setPos(cols / 2 - 10, rows / 2);
	printf("GAME END!");

	setPos(cols / 2 - 10, rows / 2 + 1);
	printf("Score: %d", this->score);

	setPos(cols / 2 - 10, rows / 2 + 2);
	printf("Press ENTER to exit");

	this->player_snake.del_snake();

	getchar();

}

void setPos(int x, int y)
{
	COORD pos;
	HANDLE hOutput;
	pos.X = x;
	pos.Y = y;
	hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hOutput, pos);
}

void game::clean_screen()
{

	for (int i = 0; i < this->cols; i++) {
		for (int j = 0; j < this->rows; j++) {

			setPos(i, j);

			printf(" ");
		}
	}

}

int get_rand(int num)
{
	srand((unsigned)time(NULL));
	return rand() % num;
}