#include "game.h"

game::game()
{
	this->rows = 30;
	this->cols = 100;

	map new_map(this->rows, this->cols);
	this->game_map = new_map;

	int snake_x = rand() % cols;
	int snake_y = rand() % rows;

	while (true) {

		if (!this->game_map.is_edge(snake_x, snake_y) && !this->game_map.is_edge(snake_x - 1, snake_y) && !this->game_map.is_edge(snake_x - 2, snake_y)) {
			break;
		}

		snake_x = rand() % cols;
		snake_y = rand() % rows;
	}

	snake new_snake(snake_x, snake_y);
	this->player_snake = new_snake;

	this->score = 0;
	
	this->food[0] = 0;
	this->food[1] = 0;
}

void game::print_game()
{

	for (int i = 0; i < cols; i++) {
		for (int j = 0; j < rows; j++) {

			setPos(i, j);

			/*if (this->game_map.is_edge(i, j) || this->player_snake.pos_has_node(i, j) || this->is_food(i, j)) {

				printf("¡ö");

			}
			else {

				printf(" ");

			}*/

			if (i == 10 && j == 5) {

				int* array = this->player_snake.next_head_position();

				if (this->game_map.is_edge(array[0], array[1])) {
					printf("HIT");
				}
				else {
					printf(" ");
				}

			}

			if (i == 10 && j == 10) {

				int* array = this->player_snake.next_head_position();

				printf("%d %d", array[0], array[1]);

			}

			if (i == 10 && j == 20) {

				int* array = this->player_snake.get_cur_position();

				printf("%d %d", array[0], array[1]);

			}

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

	int food_x = rand() % cols;
	int food_y = rand() % rows;

	while (true) {

		if (food_x != cur_x && food_y != cur_y && !this->game_map.is_edge(food_x, food_y) && !this->player_snake.pos_has_node(food_x, food_y)) {
			break;
		}

		food_x = rand() % cols;
		food_y = rand() % rows;

	}

	this->food[0] = food_x;
	this->food[1] = food_y;
}

bool game::is_food()
{
	int* next_head_pos = this->player_snake.next_head_position();

	int x = next_head_pos[0];
	int y = next_head_pos[1];

	return x == this->food[0] && y == this->food[1];
}

bool game::is_food(int x, int y)
{
	return x == this->food[0] && y == this->food[1];
}

bool game::is_game_end()
{

	int* head_pos = this->player_snake.get_cur_position();

	int x = head_pos[0];
	int y = head_pos[1];

	return this->player_snake.hit_self(x, y) || this->game_map.is_edge(x, y);

}

void game::game_start()
{
	this->generate_food();

	char str[255];
	sprintf(str, "mode con cols=%d lines=%d", this->cols, this->rows);
	system(str);

	setPos(cols / 2 - 10, rows / 2);
	printf("Press anykey to start\n");

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

			if (is_food()) {
				this->player_snake.add();
				generate_food();
				this->score++;
			}
			else {
				this->player_snake.move();
			}

			n = 0;
		}

		/*if (this->is_game_end()) {
			this->print_game();
			break;
		}*/
		n++;

	}

}

void game::game_end()
{

	setPos(cols / 2 - 10, rows / 2);
	printf("GAME END!\nScore: %d\nPress anykey to exit", this->score);

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