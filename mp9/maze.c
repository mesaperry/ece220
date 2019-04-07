#include <stdio.h>
#include <stdlib.h>
#include "maze.h"



/*
These functions were written with the purpose of serving a maze solver. The function createMaze
takes an input file name as pulls the maze and data out of that text file and stores it in a
struct called maze_t. destroyMaze frees all the dynamic data from the maze struct. printMaze
prints the current version of the maze. solveMazePDS uses recursion to solve the maze when called
upon.
*/





/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	FILE *file = fopen(fileName, "r");
	maze_t * maze = malloc(sizeof(maze_t)); //allocate memory to the struct
	int width, height;
	fscanf(file, "%d %d", &width, &height); //collect width and height from input file
	maze->width = width; //set width and height members of struct
	maze->height = height;

    maze->cells = (char **)malloc(height * sizeof(char *)); //allocate an array of pointers
	int i;
    for (i=0; i<height; i++){
         (maze->cells)[i] = (char *)malloc(width * sizeof(char)); //allocate an array to each pointer
	}

    // arr[i][j] is the same as *(*(arr+i)+j)


	char cur_char = 'a'; //set to something random to start
	int index = -1, row = 0, col = 0;
	for(i = 0; i<width*height; i++){
		cur_char = fgetc(file);
		if(cur_char!='\n'){
			index++;
			row = index/width;
			col = index%width;
			maze->cells[row][col] = cur_char; //copy cells from file to maze
		}
		if(cur_char == '\n'){ //doesn't count as an iteration if no maze
			i--;
		}
		if(cur_char == 'S'){ //set coordinates for start
			maze->startColumn = col;
			maze->startRow = row;
		}
		if(cur_char == 'E'){ //set coordinates for end
			maze->endColumn = col;
			maze->endRow = row;
		}
	}
    return maze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
	int i;
	for(i=0; i<(maze->height); i++){
		free((maze->cells)[i]);
	}
	free(maze->cells);
    free(maze);
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
	int i, j;
    for(i=0; i<(maze->height); i++){
		for(j=0; j<(maze->width); j++){
			putchar(maze->cells[i][j]);
		}
		printf("\n");
	}
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
	if(row<0 || col<0 || row>=(maze->height) || col>=(maze->width)){
		return 0; //filter out of bounds
	}
	printf("%d %d\n", row, col);
	char cell = maze->cells[row][col];
	if(cell=='%' || cell=='*' || cell=='~'){
		return 0; //filter out illegal moves
	}
    if(cell == 'E'){ //base case
		return 1;
	}

	if(cell!='S'){
		maze->cells[row][col] = '*';
	}
	if(col>0){
		if((maze->cells[row][col-1])!='S'){
			if(solveMazeDFS(maze, col-1, row)){
				return 1; //move left
			}
		}
	}
	if(row<(maze->height)-1){
		if((maze->cells[row+1][col])!='S'){
			if(solveMazeDFS(maze, col, row+1)){
				return 1; //move down
			}
		}
	}
	if(row>0){
		if((maze->cells[row-1][col])!='S'){
			if(solveMazeDFS(maze, col, row-1)){
				return 1; //move up
			}
		}
	}
	if(col<(maze->width)-1){
		if((maze->cells[row][col+1])!='S'){
			if(solveMazeDFS(maze, col+1, row)){
				return 1; //move right
			}
		}
	}
	maze->cells[row][col] = '~';
	return 0; //backtrack
}












