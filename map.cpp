#include "map.h"

map::map()
{

}

map::map(int rows, int cols)
{

	int n = rows * 2 + (cols - 2) * 2;

	int (*edge)[2] = new int[n][2];

	int index = 0;

	for (int i = 0; i < cols; i++) {

		edge[index][0] = i;
		edge[index++][1] = 0;

		edge[index][0] = i;
		edge[index++][1] = rows - 1;
	}

	for (int i = 1; i < rows - 1; i++) {

		edge[index][0] = 0;
		edge[index++][1] = i;

		edge[index][0] = cols - 1;
		edge[index++][1] = i;

	}

	this->map_edge = edge;
	this->edge_num = n;
}

bool map::is_edge(int x, int y)
{

	int n = this->edge_num;

	for (int i = 0; i < n; i++) {

		if (this->map_edge[i][0] == x && this->map_edge[i][1] == y) {

			return true;

		}

	}

	return false;
}