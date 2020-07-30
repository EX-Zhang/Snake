#ifndef SNAKE_H
#define SNAKE_H

#include <cstdlib>

#define UP 1
#define DOWN -1
#define LEFT 2
#define RIGHT -2

class snake
{
private:
	
	typedef struct snake_node {

		int x;
		int y;
		struct snake_node* next;

	}snake_node;

	snake_node* head;

	int cur_direction;

	void del_snake(snake_node* cur_node);


public:

	snake();
	snake(int x, int y);
	int next_head_position(int* x, int* y);
	void change_direction(int direction);
	void add();
	void move();
	bool pos_has_node(int x, int y);
	int get_cur_position(int* x, int* y);
	bool hit_self(int x, int y);
	bool hit_self();
	void del_snake();

};


#endif // !SNAKE_H
