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

int* snake::next_head_position()
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

	static int next_pos[2] = { cur_x,cur_y };

	return next_pos;
}

int* snake::get_cur_position()
{

	static int pos[2] = { this->head->x,this->head->y };

	return pos;
}

void snake::change_direction(int direction)
{

	if (direction != this->cur_direction&&direction != -1 * this->cur_direction) {

		this->cur_direction = direction;

	}

}

void snake::add()
{
	int* new_head_pos = this->next_head_position();
	
	snake_node* new_head = (snake_node*)malloc(sizeof(snake_node));

	new_head->x = new_head_pos[0];
	new_head->y = new_head_pos[1];
	new_head->next = this->head;

	this->head = new_head;
}

void snake::move()
{

	int* new_head_pos = this->next_head_position();

	snake_node* cur = this->head;
	snake_node* prev = NULL;

	while (cur != NULL && cur->next != NULL) {

		prev = cur;
		cur = cur->next;

	}

	cur->x = new_head_pos[0];
	cur->y = new_head_pos[1];
	cur->next = this->head;

	this->head = cur;

	prev->next = NULL;

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