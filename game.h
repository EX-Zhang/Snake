#ifndef GAME_H
#define GAME_H

#include <cstdio>
#include <cstdlib>
#include <time.h> 

#include "snake.h"
#include "map.h"

class game {

private:

	int rows, cols;
	int score;
	int food[2];
	
	snake player_snake;
	map game_map;

	bool is_game_end();
	void print_game();
	void generate_food();
	bool is_food();
	bool is_food(int x, int y);
	void clean_screen();

public:
	game();
	void game_start();
	void game_circle();
	void game_end();
};

void setPos(int x, int y);
int get_rand(int num);
#endif // !GAME_H
