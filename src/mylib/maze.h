#ifndef _MAZE_H_
#define _MAZE_H_

typedef struct
{
	int visited;
	int north;
	int east;
	int south;
	int west;
} cell;

typedef struct
{
	int i;
	int j;
	int prev;
} element;

typedef enum
{
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
} orientation;

typedef enum {
    FLYING_TO_START = 0,
    FLYING_AROUND,
    FLYING_DOWN,
    WALK_FORWARD,
    TURN_LEFT,
    TURN_RIGHT,
    IDLE,
    BEGIN,
    DONE,
} state;

void swap(int *a, int *b);
void shuffle(int arr[]);
void printArray(int arr[]);
void mazeGenerator(int x, int y);
void printmaze();
void getMaze();
int numOfWalls();
void solveMaze(int i, int j);
void solve();
void solveMazeShort();
void solveShort();
void printsol();

#endif