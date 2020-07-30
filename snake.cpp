#include "snake.h"

snake::snake()
{

}

snake::snake(int x, int y)
{

	snake_node* head = (snake_node*)malloc(sizeof(snake_node));

	head->x = x;
	head->y = y;

	snake_node* mid = (snake_node*)malloc(sizeof(snake_node));

	mid->x = x - 1;
	mid->y = y;

	head->next = mid;

	snake_node* tail = (snake_node*)malloc(sizeof(snake_node));

	tail->x = x - 2;
	tail->y = y;

	mid->next = tail;

	tail->next = NULL;

	this->head = head;
	this->cur_direction = RIGHT;

}

int snake::next_head_position(int* x, int* y)
{

	int cur_x = this->head->x;
	int cur_y = this->head->y;

	if (this->cur_direction == UP) {
		cur_y -= 1;
	}
	else if (this->cur_direction == DOWN) {
		cur_y += 1;
	}
	else if (this->cur_direction == LEFT) {
		cur_x -= 1;
	}
	else if(this->cur_direction == RIGHT) {
		cur_x += 1;
	}

	*x = cur_x;
	*y = cur_y;

	return 0;
}

int snake::get_cur_position(int* x, int* y)
{

	*x = this->head->x;
	*y = this->head->y;

	return 0;
}

void snake::change_direction(int direction)
{

	if (direction != this->cur_direction && direction != -1 * this->cur_direction) {

		this->cur_direction = direction;

	}

}

void snake::add()
{

	int x, y;

	this->next_head_position(&x, &y);
	
	snake_node* new_head = (snake_node*)malloc(sizeof(snake_node));

	new_head->x = x;
	new_head->y = y;
	new_head->next = this->head;

	this->head = new_head;
}

void snake::move()
{

	int x, y;

	this->next_head_position(&x, &y);

	snake_node* cur = this->head;

	while (cur->next->next != NULL) {

		cur = cur->next;

	}

	cur->next->next = this->head;
	this->head = cur->next;
	this->head->x = x;
	this->head->y = y;

	cur->next = NULL;

}

bool snake::pos_has_node(int x, int y)
{
	snake_node* cur = this->head;

	while (cur != NULL) {

		if (cur->x == x && cur->y == y) {

			return true;

		}

		cur = cur->next;

	}

	return false;
}

bool snake::hit_self(int x, int y)
{
	snake_node* cur = this->head->next;

	while (cur != NULL) {

		if (cur->x == x && cur->y == y) {

			return true;

		}

		cur = cur->next;

	}

	return false;
}

bool snake::hit_self()
{

	int x = this->head->x;
	int y = this->head->y;

	snake_node* cur = this->head->next;

	while (cur != NULL) {

		if (cur->x == x && cur->y == y) {

			return true;

		}

		cur = cur->next;

	}

	return false;

}

void snake::del_snake()
{

	this->del_snake(this->head);

}

void snake::del_snake(snake_node* cur_node)
{

	if (cur_node != NULL) {

		this->del_snake(cur_node->next);
		free(cur_node);

	}

}
