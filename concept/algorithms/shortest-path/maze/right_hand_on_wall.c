#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <locale.h>
#include <curses.h>

#define MAZE_WIDTH 19
#define MAZE_HEIGHT 19

#define EMPTY " "
#define MOUSE "\u25CF"

#define UP 1
#define RIGHT 2
#define DOWN 4
#define LEFT 8

#define DRAW_START_X 10
#define DRAW_START_Y 10
#define DRAW_COORD_START_X (DRAW_START_X)
#define DRAW_COORD_START_Y (DRAW_START_Y + MAZE_HEIGHT + 2)

int maze[MAZE_HEIGHT][MAZE_WIDTH] = 
	{
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
		{0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1},
		{1, 0, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 1},
		{1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1},
		{1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1},
		{1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1},
		{1, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
		{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
	};


//start x and y of mouse
int mx = MAZE_WIDTH - 1;
int my = MAZE_HEIGHT - 2;

//for recording path which mouse moved
int *records;

char *get_shape(int m[][MAZE_WIDTH], int x, int y);
void draw_shape(int x, int y, const char *shape);
void draw_coordinate(int x, int y);
int draw_maze(int m[][MAZE_WIDTH]);

void move_forward(int *x, int *y, int direction);
void right(int *direction);
void left(int *direction);
bool is_in_maze(int x, int y);
int wall_ahead(int m[][MAZE_WIDTH], int x, int y, int direction);

void record_path(int x, int y);
void del_path(int i, int j);

void right_hand(int m[][MAZE_WIDTH], int x, int y, int direction);
void shortest_path();


int main()
{
	setlocale(LC_ALL, "");

	records = (int *) malloc(MAZE_HEIGHT * MAZE_WIDTH * sizeof(int));
	if(records == NULL) {
		printf("Failed to allocate memory.\n");
		exit(EXIT_FAILURE);
	}

	initscr();

	draw_maze(maze);

	right_hand(maze, mx, my, LEFT);

	mvprintw(DRAW_COORD_START_Y + 2, DRAW_COORD_START_X, "Press any key to start shortest path");
	getch();

	shortest_path();

	getch();
	endwin();
	free(records);

	return 0;
}


char *get_shape(int m[][MAZE_WIDTH], int x, int y)
{
	static char *shape[] = {" ", "\u2502", "\u2500", "\u2514", "\u2502", "\u2502", "\u250c", "\u251c", "\u2500", "\u2518", "\u2500", "\u2534", "\u2510", "\u2524", "\u252c", "\u253c"};
	
	int s = 0;
	if(m[y][x]) {
		if(y > 0 && m[y - 1][x]) {
			s |= UP;
		}
		if(y < MAZE_HEIGHT - 2 && m[y + 1][x]) {
			s |= DOWN;
		}
		if(x > 0 && m[y][x - 1]) {
			s |= LEFT;
		}
		if(x < MAZE_WIDTH - 2 && m[y][x + 1]) {
			s |= RIGHT;
		}
	}

	return shape[s];
}
void draw_shape(int x, int y, const char *shape)
{
	mvprintw(DRAW_START_Y + y, DRAW_START_X + x, "%s", shape);
	refresh();
}
void draw_coordinate(int x, int y)
{
	mvprintw(DRAW_COORD_START_Y, DRAW_COORD_START_X, "current coordinate: [%2d, %2d]", x, y);
	refresh();
}
int draw_maze(int m[][MAZE_WIDTH])
{
	for(int j = 0; j < MAZE_HEIGHT; j++) {
		for(int i = 0; i < MAZE_WIDTH; i++) {
			draw_shape(i, j, get_shape(m, i, j));
		}
	}
}

void move_forward(int *x, int *y, int direction)
{
	draw_shape(*x, *y, EMPTY);
	
	*x = (direction == LEFT) ? --(*x) :
		(direction == RIGHT) ? ++(*x) : *x;
	*y = (direction == UP) ? --(*y) :
		(direction == DOWN) ? ++(*y) : *y;

	record_path(*x, *y);
	
	draw_shape(*x, *y, MOUSE);
}
void right(int *direction)
{
	*direction <<= 1;
	*direction = (*direction > LEFT) ? UP : *direction;
}
void left(int *direction)
{
	*direction >>= 1;
	*direction = (*direction == 0) ? LEFT : *direction;
}
bool is_in_maze(int x, int y)
{
	if(x > 0 && x < MAZE_WIDTH - 1 && y > 0 && y < MAZE_HEIGHT - 1) {
		return true;
	}

	return false;
}
int wall_ahead(int m[][MAZE_WIDTH], int x, int y, int direction)
{
	x = (direction == LEFT) ? --x :
		(direction == RIGHT) ? ++x : x;
	y = (direction == UP) ? --y :
		(direction == DOWN) ? ++y : y;

	return m[y][x];
}

void record_path(int x, int y)
{
	static int index = 0;
	
	records[index++] = x;
	records[index++] = y;
}
void del_path(int i, int j)
{
	while(records[j] >= 0) {
		records[i++] = records[j++];
	}
	records[i] = -1;
}
void right_hand(int m[][MAZE_WIDTH], int x, int y, int direction)
{
	draw_shape(x, y, MOUSE);
	record_path(x, y);

	move_forward(&x, &y, direction);
	draw_coordinate(x, y);

	while(is_in_maze(x, y)) {
		usleep(50000);
		right(&direction);
		while(wall_ahead(m, x, y, direction)) {
			left(&direction);
		}
		move_forward(&x, &y, direction);
		draw_coordinate(x, y);
	}

	record_path(-1, -1);
	draw_shape(x, y, EMPTY);
}
void shortest_path()
{
	int i = 0;
	int x, y;

	int j;
	int x1, y1;

	while(records[i] >= 0) {
		x = records[i];
		y = records[i + 1];
		j = i + 2;
		while(records[j] >= 0) {
			x1 = records[j];
			y1 = records[j + 1];
			if(x == x1 && y == y1) {
				del_path(i, j);
			}
			j += 2;
		}
		i += 2;
	}
	
	i = 0;
	while(records[i] >= 0) {
		x = records[i++];
		y = records[i++];
		draw_shape(x, y, MOUSE);
		draw_coordinate(x, y);
		usleep(50000);
		draw_shape(x, y, EMPTY);
	}
}
