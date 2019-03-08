/* These functions were written by Mesa Perry.
They are used in conjunction with some other files
to simulate the game of life. The function countLiveNeighbor
counts the number of neighboring cells given inputs of the
board, the dimensions, and the row and column of the specified
cell. The function updateBoard updates the input board to the
next state using the countLiveNeighbor function and the rules
of the game. The function aliveStable uses updateBoard to test
if the next state will be the same as the current one.
*/


/*
 * countLiveNeighbor
 * Inputs:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * row: the row of the cell that needs to count alive neighbors.
 * col: the col of the cell that needs to count alive neighbors.
 * Output:
 * return the number of alive neighbors. There are at most eight neighbors.
 * Pay attention for the edge and corner cells, they have less neighbors.
 */
 
int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
    int cellNumber = col + row * boardColSize;
    int count = 0;
    if(row == 0 && col == 0){ //detect upper left corner cells
        if (board[cellNumber + 1]){ //check cell to the right
            count ++;
        }
        if (board[cellNumber + boardColSize]){ //check cell below
            count ++;
        }
        if (board[cellNumber + boardColSize + 1]){ //check cell to bottom right
            count ++;
        }
    }
    else if(row == 0 && col == boardColSize - 1){ //detect upper right corner cells
        if (board[cellNumber - 1]){ //check cell to the left
            count ++;
        }
        if (board[cellNumber + boardColSize]){ //check cell below
            count ++;
        }
        if (board[cellNumber + boardColSize - 1]){ //check cell to bottom left
            count ++;
        }
    }
    else if(row == boardRowSize - 1 && col == 0){ //detect lower left corner cells
        if (board[cellNumber + 1]){ //check cell to the right
            count ++;
        }
        if (board[cellNumber - boardColSize]){ //check cell above
            count ++;
        }
        if (board[cellNumber - boardColSize + 1]){ //check cell to upper right
            count ++;
        }
    }
    else if(row == boardRowSize - 1 && col == boardColSize - 1){ //detect lower right corner cells
        if (board[cellNumber - 1]){ //check cell to the left
            count ++;
        }
        if (board[cellNumber - boardColSize]){ //check cell above
            count ++;
        }
        if (board[cellNumber - boardColSize - 1]){ //check cell to upper left
            count ++;
        }
    }
   
    else if(row == 0){ //detect upper edge cells that aren't corners
        if (board[cellNumber + 1]){ //check cell to the right
            count ++;
        }
        if (board[cellNumber - 1]){ //check cell to the left
            count ++;
        }
        if (board[cellNumber + boardColSize]){ //check cell below
            count ++;
        }
        if (board[cellNumber + boardColSize + 1]){ //check cell to bottom right
            count ++;
        }
        if (board[cellNumber + boardColSize - 1]){ //check cell to bottom left
            count ++;
        }
    }
    else if(row == boardRowSize - 1){ //detect lower edge cells that aren't corners
        if (board[cellNumber + 1]){ //check cell to the right
            count ++;
        }
        if (board[cellNumber - 1]){ //check cell to the left
            count ++;
        }
        if (board[cellNumber - boardColSize]){ //check cell above
            count ++;
        }
        if (board[cellNumber - boardColSize + 1]){ //check cell to upper right
            count ++;
        }
        if (board[cellNumber - boardColSize - 1]){ //check cell to upper left
            count ++;
        }
    }
    else if(col == 0){ //detect left edge cells that aren't corners
        if (board[cellNumber + 1]){ //check cell to the right
            count ++;
        }
        if (board[cellNumber + boardColSize]){ //check cell below
            count ++;
        }
        if (board[cellNumber - boardColSize]){ //check cell above
            count ++;
        }
        if (board[cellNumber + boardColSize + 1]){ //check cell to bottom right
            count ++;
        }
        if (board[cellNumber - boardColSize + 1]){ //check cell to upper right
            count ++;
        }
    }
    else if(col == boardColSize - 1){ //detect right edge cells that aren't corners
        if (board[cellNumber - 1]){ //check cell to the left
            count ++;
        }
        if (board[cellNumber + boardColSize]){ //check cell below
            count ++;
        }
        if (board[cellNumber - boardColSize]){ //check cell above
            count ++;
        }
        if (board[cellNumber + boardColSize - 1]){ //check cell to bottom left
            count ++;
        }
        if (board[cellNumber - boardColSize - 1]){ //check cell to upper left
            count ++;
        }
    }
   
    else{ //for everything else ie. non edges
        if (board[cellNumber + 1]){ //check cell to the right
            count ++;
        }
        if (board[cellNumber - 1]){ //check cell to the left
            count ++;
        }
        if (board[cellNumber + boardColSize]){ //check cell below
            count ++;
        }
        if (board[cellNumber - boardColSize]){ //check cell above
            count ++;
        }
        if (board[cellNumber + boardColSize + 1]){ //check cell to bottom right
            count ++;
        }
        if (board[cellNumber - boardColSize + 1]){ //check cell to upper right
            count ++;
        }
        if (board[cellNumber + boardColSize - 1]){ //check cell to bottom left
            count ++;
        }
        if (board[cellNumber - boardColSize - 1]){ //check cell to upper left
            count ++;
        }
    }
    return count;
}

/*
 * Update the game board to the next step.
 * Input:
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */
void updateBoard(int* board, int boardRowSize, int boardColSize) {
	int newBoard[boardRowSize*boardColSize];
	for(int i = 0; i < boardRowSize * boardColSize; i ++){ //create a copy of the board
		newBoard[i] = board[i];
	}
    for(int row = 0; row < boardRowSize; row ++){
        for(int col = 0; col < boardColSize; col ++){
            int neighbors = countLiveNeighbor(board, boardRowSize, boardColSize, row, col);
            if(board[col + row * boardColSize] && (neighbors < 2 || neighbors > 3)){
                newBoard[col + row * boardColSize] = 0; //if the cell is alive and has <2 or >3 neighbors, it dies
            }
            if(neighbors == 3){
                newBoard[col + row * boardColSize] = 1; //if the cell has 3 neighbors, it revives
            }
        }
    }
	for(int i = 0; i < boardRowSize * boardColSize; i ++){ //copy the changes over
		board[i] = newBoard[i];
	}
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */
int aliveStable(int* board, int boardRowSize, int boardColSize){
	int inconsistancies = 0;
	int futureBoard[boardRowSize*boardColSize];
	for(int i = 0; i < boardRowSize*boardColSize; i ++){ //create a copy of the board
		futureBoard[i] = board[i];
	}
	updateBoard(futureBoard, boardRowSize, boardColSize);
    for(int i = 0; i < boardRowSize*boardColSize; i ++){ //loop through each cell
        if(board[i] != futureBoard[i]){
            inconsistancies ++; //increment whenever there is a change
        }
    }
	if(inconsistancies){
		return 0;
	}
	else{
		return 1;
	}
}
