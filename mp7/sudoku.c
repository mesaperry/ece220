#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------


/*
The functions is_val_in_row, is_val_in_col, is_val_in_3x3_zone, is_val_valid, and solve_sudoku were
written by Mesa Perry, with the purpose of solving sudoku puzzles. Function is_val_in_row checks if
the input value is contained in the given row of the given sudoku board. Functions is_val_in_col
and is_val_in_3x3_zone do the same, except with columns and zones, respectively. The function
is_val_valid combines these three functions to check whether a value is possible to be placed in a
cell, based on the rules of sudoku. The function solve_sudoku uses the function is_val_valid and 
recursion to solve input sudoku puzzles. It checks whether each combination works, and moves on
until it finds one that works.
*/





// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
	int exist = 0;
	for(int count = 0; count < 9; count ++){ //iterate through each col in row
		if(sudoku[i][count] == val){ //if cell contains the value
			exist ++; //count when val is detected
		}
	}
	if(exist){
		return 1;
	}
	else{
		return 0;
	}
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
	int exist = 0;
	for(int count = 0; count < 9; count ++){ //iterate through each row in col
		if(sudoku[count][j] == val){ //if cell contains the value
			exist ++; //count when val is detected
		}
	}
	if(exist){
		return 1;
	}
	else{
		return 0;
	}
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
	int exist = 0;
	if(0 <= i && i <= 2){ //check upper three zones
		if(0 <= j && j <= 2){ //check left zone
			for(int icount = 0; icount < 3; icount ++){
				for(int jcount = 0; jcount < 3; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
		if(3 <= j && j <= 5){ //check middle zone
			for(int icount = 0; icount < 3; icount ++){
				for(int jcount = 3; jcount < 6; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
		if(6 <= j && j <= 8){ //check right zone
			for(int icount = 0; icount < 3; icount ++){
				for(int jcount = 6; jcount < 9; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
	}
	if(3 <= i && i <= 5){ //check middle three zones
		if(0 <= j && j <= 2){ //check left zone
			for(int icount = 3; icount < 6; icount ++){
				for(int jcount = 0; jcount < 3; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
		if(3 <= j && j <= 5){ //check middle zone
			for(int icount = 3; icount < 6; icount ++){
				for(int jcount = 3; jcount < 6; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
		if(6 <= j && j <= 8){ //check right zone
			for(int icount = 3; icount < 6; icount ++){
				for(int jcount = 6; jcount < 9; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
	}
	if(6 <= i && i <= 8){ //check lower three zones
		if(0 <= j && j <= 2){ //check left zone
			for(int icount = 6; icount < 9; icount ++){
				for(int jcount = 0; jcount < 3; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
		if(3 <= j && j <= 5){ //check middle zone
			for(int icount = 6; icount < 9; icount ++){
				for(int jcount = 3; jcount < 6; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
		if(6 <= j && j <= 8){ //check right zone
			for(int icount = 6; icount < 9; icount ++){
				for(int jcount = 6; jcount < 9; jcount ++){
					if(sudoku[icount][jcount] == val){
						exist ++;
					}
				}
			}
		}
	}
	if(exist){ //if any instances of the val exists, return 1
		return 1;
	}
	else{
		return 0;
	}
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  	if(!is_val_in_row(val, i, sudoku) && !is_val_in_col(val, j, sudoku) && !is_val_in_3x3_zone(val, i, j, sudoku)){
		return 1; //return 1 if val is not detected in row, col, or 3x3 zone
  	}
	else{
		return 0; //or else return 0
	}
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
	int i, j;
	int unassigned = 0;
	for(int rowcheck = 0; rowcheck < 9; rowcheck ++){
		for(int colcheck = 0; colcheck < 9; colcheck ++){
			if(sudoku[rowcheck][colcheck] == 0){ //iterate through the board and check for empty cells
				unassigned ++; //count empty cells
				i = rowcheck; //save row of empty cell
				j = colcheck; //save col of empty cell
			}
		}
	}
	if(unassigned == 0) {
		return true; //if all cells are filled, return true
	}
   
	for (int num = 1; num <= 9; num++) { //iterate through all possible numbers
		if (is_val_valid(num, i, j, sudoku)) { //check if the number is valid to place in the empty cell
			sudoku[i][j] = num; //try putting number in
			if (solve_sudoku(sudoku)) { //use recursion to test if any combination using this is possible
				return true; //if it works, return true
			}
			sudoku[i][j] = 0; //doesn't work, set it back to empty cell
		}
	}
	return false; //no solution was found, return false
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}





