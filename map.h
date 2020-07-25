#ifndef MAP_H
#define MAP_H

#include <windows.h>

class map {

private:
	int (*map_edge)[2];
	int edge_num;

public:
	map();
	map(int rows, int cols);
	bool is_edge(int x, int y);
};

#endif // !MAP_H
