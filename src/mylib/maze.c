#include "maze.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

cell maze[8][8];

void swap(int *a, int *b) { 
	int temp = *a;
	*a = *b;
	*b = temp;
}

void shuffle(int arr[]) {
	for (int i = 3; i > 0; i--) {
		int j = rand() % (i+1);
		swap(&arr[i], &arr[j]);
	}
}

void printArray(int arr[]) { 
	for (int i = 0; i < 4; i++)
		printf("%d ", arr[i]); 
	printf("\n"); 
} 

void mazeGenerator(int x, int y) {
	/*Given a current cell as a parameter,
	Mark the current cell as visited
	While the current cell has any unvisited neighbour maze
		Choose one of the unvisited neighbours
		Remove the wall between the current cell and the chosen cell
		Invoke the routine recursively for a chosen cell*/
	int rand[] = {1, 2, 3, 4};
	shuffle(rand);
	//printArray(rand);
	
	maze[x][y].visited = 1;
	
	int i, direction;
	for (i = 0; i < 4; i++) {
		direction = rand[i];
		switch (direction) {
			case 1: //north
				if (x > 0) {
					if (maze[x-1][y].visited == 0) {
						maze[x][y].north = 0;
						maze[x-1][y].south = 0;
						mazeGenerator(x-1,y);
					}
				}
				break;
			case 2: //south
				if (x < 7) {
					if (maze[x+1][y].visited == 0) {
						maze[x][y].south = 0;
						maze[x+1][y].north = 0;
						mazeGenerator(x+1,y);
					}
				}
				break;
			case 3: //east
				if (y < 7) {
					if (maze[x][y+1].visited == 0) {
						maze[x][y].east = 0;
						maze[x][y+1].west = 0;
						mazeGenerator(x,y+1);
					}
				}
				break;
			case 4: //west
				if (y > 0) {
					if (maze[x][y-1].visited == 0) {
						maze[x][y].west = 0;
						maze[x][y-1].east = 0;
						mazeGenerator(x,y-1);
					}
				}
				break;
		}
	}
}

void printmaze() {
	int i, j;
	for (i = 0; i < 8; i++) {
		// top walls
		for (j = 0; j < 8; j++) {
			printf("+");
			if (maze[i][j].north == 1) printf("--"); else printf("  ");
		}
		printf("+");
		printf("\n");
		
		// side walls
		for (j = 0; j < 8; j++) {
			if (maze[i][j].west == 1) printf("|"); else printf(" ");
			printf("  ");
		}
		if (maze[i][7].east == 1) printf("|"); else printf(" ");
		printf("\n");
	}
	// top walls
	for (j = 0; j < 8; j++) {
		printf("+");
		if (maze[7][j].south == 1) printf("--"); else printf("  ");
	}
	printf("+");
	printf("\n");
}

void getMaze() {
	srand ( time(NULL) ); 
	//build every possible wall
	int i, j;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++) {
			maze[i][j].visited = 0;
			maze[i][j].north = 1;
			maze[i][j].east = 1;
			maze[i][j].south = 1;
			maze[i][j].west = 1;
		}
	}
	
	mazeGenerator(0,0);
	
	//build entrances
	maze[0][0].west = 0;
	maze[7][7].east = 0;
}

int numOfWalls() {
	int i, j, numOfWalls = 0;
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 8; j++)
			if (maze[i][j].north == 1) numOfWalls++;
		for (j = 0; j < 8; j++)
			if (maze[i][j].west == 1) numOfWalls++;
		if (maze[i][7].east == 1) numOfWalls++;
	}
	for (j = 0; j < 8; j++)
		if (maze[7][j].south == 1) numOfWalls++;
	return numOfWalls;
}

//

orientation facing = EAST;
state solution[500];
int curr_state = 0;

void solveMaze(int i, int j) 
{
	if ((i == 7) && (j == 8))
	{
		//solution[curr_state] = DONE;  //printf("%d,%d DONE\n", i, j);
		solution[curr_state] = TURN_LEFT;
		curr_state++;
		solution[curr_state] = TURN_LEFT;
		curr_state++;
		solution[curr_state] = WALK_FORWARD;
		curr_state++;
		printf("total steps: %d\n",curr_state);
		return;
	}
	else if (j == 56)
	{
		return;
	}
	else
	{
		// EAST //
		if (facing == EAST)
		{
			// if hand on left wall
			if (maze[i][j].north == 1)
			{
				// if wall not in front of them, go forward
				if (maze[i][j].east == 0) {
					solution[curr_state] = WALK_FORWARD; //printf("%d,%d walk forward (east)\n", i, j);
					curr_state++;
					solveMaze(i, j+1);  //move forward east
				}
				// if wall also in front of them, turn right
				else 
				{
					solution[curr_state] = TURN_LEFT; //RIGHT; //printf("%d,%d turn right (east)\n", i, j);
					facing = SOUTH;
					curr_state++;
					solveMaze(i, j);  //did not move
				}
			}
			// no hand on left wall
			else
			{
				// turn LEFT
				solution[curr_state] = TURN_RIGHT; //LEFT; //printf("%d,%d turn left (east)\n", i, j);
				facing = NORTH;
				curr_state++;
				// then move forward if possible
				if (maze[i][j].north == 0)
				{
					solution[curr_state] = WALK_FORWARD;  //printf("%d,%d walk forward (east)\n", i, j);
					curr_state++;
					solveMaze(i-1, j); //move forward north
				}
				else
				{
					solveMaze(i, j); //did not move
				}
			}
		}
		
		// NORTH //
		else if (facing == NORTH)
		{
			// if hand on left wall
			if (maze[i][j].west == 1)
			{
				// if wall not in front of them, go forward
				if (maze[i][j].north == 0) {
					solution[curr_state] = WALK_FORWARD;  //printf("%d,%d walk forward (north)\n", i, j);
					curr_state++;
					solveMaze(i-1, j);  //move forward NORTH
				}
				// if wall also in front of them, turn right
				else 
				{
					solution[curr_state] = TURN_LEFT; //RIGHT;  //printf("%d,%d turn right (north)\n", i, j);
					facing = EAST;
					curr_state++;
					solveMaze(i, j);  //did not move
				}
			}
			// no hand on left wall
			else
			{
				// turn LEFT
				solution[curr_state] = TURN_RIGHT; //LEFT;  //printf("%d,%d turn left (north)\n", i, j);
				facing = WEST;
				curr_state++;
				// then move forward if possible
				if (maze[i][j].west == 0)
				{
					solution[curr_state] = WALK_FORWARD; //printf("%d,%d walk forward (north)\n", i, j);
					curr_state++;
					solveMaze(i, j-1); //move forward WEST
				}
				else
				{
					solveMaze(i, j); //did not move
				}
			}
		}
		
		// WEST //
		else if (facing == WEST)
		{
			// if hand on left wall
			if (maze[i][j].south == 1)
			{
				// if wall not in front of them, go forward
				if (maze[i][j].west == 0) {
					solution[curr_state] = WALK_FORWARD; //printf("%d,%d walk forward (west)\n", i, j);
					curr_state++;
					solveMaze(i, j-1);  //move forward WEST
				}
				// if wall also in front of them, turn right
				else 
				{
					solution[curr_state] = TURN_LEFT; //RIGHT;  //printf("%d,%d turn right (west)\n", i, j);
					facing = NORTH;
					curr_state++;
					solveMaze(i, j);  //did not move
				}
			}
			// no hand on left wall
			else
			{
				// turn LEFT
				solution[curr_state] = TURN_RIGHT; //LEFT;  //printf("%d,%d turn left (west)\n", i, j);
				facing = SOUTH;
				curr_state++;
				// then move forward if possible
				if (maze[i][j].south == 0)
				{
					solution[curr_state] = WALK_FORWARD; //printf("%d,%d walk forward (west)\n", i, j);
					curr_state++;
					solveMaze(i+1, j); //move forward SOUTH
				}
				else
				{
					solveMaze(i, j); //did not move
				}
			}
		}
		
		// SOUTH //
		else if (facing == SOUTH)
		{
			// if hand on left wall
			if (maze[i][j].east == 1)
			{
				// if wall not in front of them, go forward
				if (maze[i][j].south == 0) {
					solution[curr_state] = WALK_FORWARD; //printf("%d,%d walk forward (south)\n", i, j);
					curr_state++;
					solveMaze(i+1, j);  //move forward SOUTH
				}
				// if wall also in front of them, turn right
				else 
				{
					solution[curr_state] = TURN_LEFT; //RIGHT;  //printf("%d,%d turn right (south)\n", i, j);
					facing = WEST;
					curr_state++;
					solveMaze(i, j);  //did not move
				}
			}
			// no hand on left wall
			else
			{
				// turn LEFT
				solution[curr_state] = TURN_RIGHT; //LEFT; //printf("%d,%d turn left (south)\n", i, j);
				facing = EAST;
				curr_state++;
				// then move forward if possible
				if (maze[i][j].east == 0)
				{
					solution[curr_state] = WALK_FORWARD; //printf("%d,%d walk forward (south)\n", i, j);
					curr_state++;
					solveMaze(i, j+1); //move forward EAST
				}
				else
				{
					solveMaze(i, j); //did not move
				}
			}
		}
	}
}

void solve()
{
	facing = EAST;
	curr_state = 0;

	// statePING INTO THE MAZE
	solution[curr_state] = WALK_FORWARD; //printf("%d,%d walk forward (south)\n", i, j);
	curr_state++;

	solveMaze(0,0);
}

//

/*typedef struct
{
	int i;
	int j;
	int prev;
} element;*/

int curr = 0;
int totalCells = 0;
element queue[100];

void solveMazeShort()
{
	while(1) {
		//mark current cell as visited
		maze[queue[curr].i][queue[curr].j].visited = 1;

		//if current cell is the last cell, we made it
		if (queue[curr].i == 7 && queue[curr].j == 7) {
			return;
		}

		//otherwise, add neighbors to queue
		else {
			// north
			if (queue[curr].i > 0)
				if (maze[queue[curr].i-1][queue[curr].j].visited == 0 && maze[queue[curr].i][queue[curr].j].north == 0) {
					queue[totalCells].i = queue[curr].i-1;
					queue[totalCells].j = queue[curr].j;
					queue[totalCells].prev = curr;
					totalCells++;
				}
			// south
			if (queue[curr].i < 7)
				if (maze[queue[curr].i+1][queue[curr].j].visited == 0 && maze[queue[curr].i][queue[curr].j].south == 0) {
					queue[totalCells].i = queue[curr].i+1;
					queue[totalCells].j = queue[curr].j;
					queue[totalCells].prev = curr;
					totalCells++;
				}
			// east
			if (queue[curr].j < 7)
				if (maze[queue[curr].i][queue[curr].j+1].visited == 0 && maze[queue[curr].i][queue[curr].j].east == 0) {
					queue[totalCells].i = queue[curr].i;
					queue[totalCells].j = queue[curr].j+1;
					queue[totalCells].prev = curr;
					totalCells++;
				}
			// west
			if (queue[curr].j > 0)
				if (maze[queue[curr].i][queue[curr].j-1].visited == 0 && maze[queue[curr].i][queue[curr].j].west == 0) {
					queue[totalCells].i = queue[curr].i;
					queue[totalCells].j = queue[curr].j-1;
					queue[totalCells].prev = curr;
					totalCells++;
				}
			curr++;
		}
	}
}

void solveShort()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			maze[i][j].visited = 0;
		}
	}

	queue[totalCells].i = 0;
	queue[totalCells].j = 0;
	queue[totalCells].prev = -1;
	totalCells++;

	solveMazeShort();

	facing = WEST;

	int z = curr;
	while (z != -1) {

		if (queue[z].i == 0 && queue[z].j == 0) break;

		if (facing == WEST) {
			//turn right
			if (queue[z].i - queue[queue[z].prev].i == 1) {
				printf("%d,%d turn right (west)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_LEFT; //RIGHT;
				curr_state++;
				facing = NORTH;
			}
			//turn left
			else if (queue[z].i - queue[queue[z].prev].i == -1) {
				printf("%d,%d turn left (west)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_RIGHT; //LEFT;
				curr_state++;
				facing = SOUTH;
			}
			// go straight
			else if (queue[z].j - queue[queue[z].prev].j == 1) {
				solution[curr_state] = WALK_FORWARD;  printf("%d,%d walk forward (west)\n", queue[z].i, queue[z].j);
				curr_state++;
				z = queue[z].prev;
			}
		}
		else if (facing == NORTH) {
			//turn right
			if (queue[z].j - queue[queue[z].prev].j == -1) {
				printf("%d,%d turn right (north)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_LEFT; //RIGHT;
				curr_state++;
				facing = EAST;
			}
			//turn left
			else if (queue[z].j - queue[queue[z].prev].j == 1) {
				printf("%d,%d turn left (north)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_RIGHT; //LEFT;
				curr_state++;
				facing = WEST;
			}
			// go straight
			else if (queue[z].i - queue[queue[z].prev].i == 1) {
				solution[curr_state] = WALK_FORWARD;  printf("%d,%d walk forward (north)\n", queue[z].i, queue[z].j);
				curr_state++;
				z = queue[z].prev;
			}
		}
		else if (facing == EAST) {
			//turn right
			if (queue[z].i - queue[queue[z].prev].i == -1) {
				printf("%d,%d turn right (east)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_LEFT; //RIGHT;
				curr_state++;
				facing = SOUTH;
			}
			//turn left
			else if (queue[z].i - queue[queue[z].prev].i == 1) {
				printf("%d,%d turn left (east)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_RIGHT; //LEFT;
				curr_state++;
				facing = NORTH;
			}
			// go straight
			else if (queue[z].j - queue[queue[z].prev].j == -1) {
				solution[curr_state] = WALK_FORWARD; printf("%d,%d walk forward (east)\n", queue[z].i, queue[z].j);
				curr_state++;
				z = queue[z].prev;
			}
		}
		else if (facing == SOUTH) {
			//turn right
			if (queue[z].j - queue[queue[z].prev].j == 1) {
				printf("%d,%d turn right (south)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_LEFT; //RIGHT;
				curr_state++;
				facing = WEST;
			}
			//turn left
			else if (queue[z].j - queue[queue[z].prev].j == -1) {
				printf("%d,%d turn left (south)\n", queue[z].i, queue[z].j);
				solution[curr_state] = TURN_RIGHT; //LEFT;
				curr_state++;
				facing = EAST;
			}
			// go straight
			else if (queue[z].i - queue[queue[z].prev].i == -1) {
				solution[curr_state] = WALK_FORWARD; printf("%d,%d walk forward (south)\n", queue[z].i, queue[z].j);
				curr_state++;
				z = queue[z].prev;
			}
		}
	}

	if (facing == NORTH){
		solution[curr_state] = TURN_RIGHT;
		curr_state++;
	}
	solution[curr_state] = WALK_FORWARD;
	curr_state++;
	solution[curr_state] = DONE;
	curr_state++;
}

void printsol()
{
	for (int i = 0; i < 350; i++)
	{
		if (solution[i] == DONE) {
			printf("DONE\n");
			break;
		}
		else if (solution[i] == WALK_FORWARD) {
			printf("walk forward\n");
		}
		else if (solution[i] == TURN_RIGHT) {
			printf("turn right\n");
		}
		else if (solution[i] == TURN_LEFT) {
			printf("turn left\n");
		}
	}
}
/*
typedef enum
{
    NORTH = 0,
    SOUTH,
    EAST,
    WEST,
} orientation;

typedef enum
{
    S_WALK_FORWARD = 0,
    S_TURN_RIGHT,
    S_TURN_LEFT,
    S_DONE,
} state;
*/