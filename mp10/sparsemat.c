#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>

/*
Written by Mesa Perry. The functions below are intended to provide functions to matrices, including various
transformations. the function load_tuples() takes an input file and turns it into a linked list matrix.
The function gv_tuples() takes an input matrix, row and colomn, and returns the value at that location.
The function set_tuples() takes an input matrix, row, column, and value, and sets that location to that
value within that matrix. The function save_tuples() writes the matrix to the specified file. The function
add_tuples() takes the two input matrices, adds them, and returns the sum matrix as an output. The
function mult_tuples() takes the two input matrices, multiplies them, and returns the product matrix as an
output.
*/



sp_tuples * load_tuples(char* input_file)
{
	FILE *file = fopen(input_file, "r");
	int width, height;
	fscanf(file, "%d %d", &height, &width); //collect width and height from input file
	sp_tuples * matrix = malloc(sizeof(sp_tuples)); //allocate memory to the sp_tuples struct
	matrix->m = height;
	matrix->n = width;
	int nz = 0;
	while(1){ //creates nodes backward
		int row, col;
		float val;
		fscanf(file, "%d %d %f", &row, &col, &val); //collect row, col, and val from input file
		if(feof(file)){
			break;
		}
		//printf("%d %d %f\n", row, col, val);
		set_tuples(matrix, row, col, val);
		nz++;
	}
/*
	while(1){ //for sorting in ascending order and deleting extras
		int i, j, k;
		int outoforder = 0, oldmatrixindex = -1024;
		for(i=0; i<nz; i++){ //iterate across each tuplet
			sp_tuples_node * currenttuplet = tuplepointer->tuples_head;
			for(j=0; j<i; j++){ //navigate to the correct tuplet
				currenttuplet = currenttuplet->next;
			}
			//printf("%d %d %d %d\n", currenttuplet->row, currenttuplet->col, outoforder, i);
			int matrixindex = ((currenttuplet->row)*width)+(currenttuplet->col);
			if(matrixindex < oldmatrixindex){ //out of order
				sp_tuples_node * abstuplet1;
				sp_tuples_node * abstuplet2;
				sp_tuples_node * abstuplet3;
				if(i!=1){ //get values
					currenttuplet = tuplepointer->tuples_head;
					for(k=0; k<i-2; k++){ //navigate to the correct tuplet
						currenttuplet = currenttuplet->next;
					}
					abstuplet1 = currenttuplet;
				}
				currenttuplet = tuplepointer->tuples_head;
				for(k=0; k<i-1; k++){ //navigate to the correct tuplet
					currenttuplet = currenttuplet->next;
				}
				abstuplet2 = currenttuplet;
				currenttuplet = tuplepointer->tuples_head;
				for(k=0; k<i; k++){ //navigate to the correct tuplet
					currenttuplet = currenttuplet->next;
				}
				abstuplet3 = currenttuplet;

				if(i!=1){ //set values
					abstuplet1->next = abstuplet3;
				}
				else{
					tuplepointer->tuples_head = abstuplet3;
				}
				abstuplet2->next = abstuplet3->next;
				abstuplet3->next = abstuplet2;
				outoforder++;
				break;
			}
			else if(matrixindex==oldmatrixindex){ //duplicate
				sp_tuples_node * nextpointer = currenttuplet->next;
				double tempvalue = currenttuplet->value;
				free(currenttuplet);
				currenttuplet = tuplepointer->tuples_head;
				for(k=0; k<i-1; k++){ //navigate to the correct tuplet
					currenttuplet = currenttuplet->next;
				}
				currenttuplet->next = nextpointer;
				currenttuplet->value = tempvalue;
				nz--;
			}
			oldmatrixindex = matrixindex;
		}
		if(!outoforder){ //exit loop when tuplets are all in order
			break;
		}
	}*/
	matrix->nz = nz;
    return matrix;
}


double gv_tuples(sp_tuples * mat_t,int row,int col)

{
	int valuefound = 0;
	double value;
	sp_tuples_node * currenttuplet = mat_t->tuples_head;
	while(currenttuplet!=NULL){ //iterate through the nodes
		if(row==currenttuplet->row && col==currenttuplet->col){
			value = currenttuplet->value;
			valuefound = 1;
			break;
		}
		currenttuplet = currenttuplet->next;
	}
	if(valuefound){
		return value;
	}
	else{
    	return 0;
	}
}



void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
	if(value==0 && gv_tuples(mat_t, row, col)){ //if set value is 0 and the cell already exists as another value
		sp_tuples_node * currenttuplet = mat_t->tuples_head;
		sp_tuples_node * pointerToNext;
		int count = 0;
		while(currenttuplet!=NULL){ //iterate through the nodes
			if(row==currenttuplet->row && col==currenttuplet->col){ //find and delete the duplicate tuple
				pointerToNext = currenttuplet->next; //save pointer to next tuple
				free(currenttuplet);
				break;
			}
			count++;
			currenttuplet = currenttuplet->next;
		}
		int i;
		currenttuplet = mat_t->tuples_head;
		for(i=1; i<count; i++){ //go to previous tuple
			currenttuplet = currenttuplet->next;
		}
		currenttuplet->next = pointerToNext; //relink the tuples
		(mat_t->nz)--;
	}
	else{ //for nonzero values being set
		int nodeChanged = 0;
		sp_tuples_node * currentNode = mat_t->tuples_head;
		if(currentNode == NULL){ //if no nodes exist
			sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
			newNode->row = row;
			newNode->col = col;
			newNode->value = value;
			newNode->next = NULL;
			mat_t->tuples_head = newNode;
			(mat_t->nz) ++;
			nodeChanged++;
		}
		else if((row*(mat_t->n)+col) < (currentNode->row)*(mat_t->n)+(currentNode->col)){ //insert new node at beginning
			sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
			newNode->row = row;
			newNode->col = col;
			newNode->value = value;
			newNode->next = currentNode;
			mat_t->tuples_head = newNode;
			(mat_t->nz) ++;
			nodeChanged++;
		}
		else{ //insert node after beginning or replace
			sp_tuples_node * previousNode;
			while(currentNode != NULL){
				if((row*(mat_t->n)+col) == (currentNode->row)*(mat_t->n)+(currentNode->col)){ //replace
					currentNode->value = value;
					nodeChanged++;
					break;
				}
				else if((row*(mat_t->n)+col) < (currentNode->row)*(mat_t->n)+(currentNode->col)){ //passed insert point
					sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
					newNode->row = row;
					newNode->col = col;
					newNode->value = value;
					newNode->next = currentNode;
					previousNode->next = newNode;
					(mat_t->nz) ++;
					nodeChanged++;
					break;
				}
				previousNode = currentNode;
				currentNode = currentNode->next;
			}
			if(!nodeChanged){ //append new node to end
				sp_tuples_node * newNode = malloc(sizeof(sp_tuples_node));
				newNode->row = row;
				newNode->col = col;
				newNode->value = value;
				newNode->next = NULL;
				previousNode->next = newNode;
				(mat_t->nz) ++;
			}
		}
	}
    return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
	FILE *file = fopen(file_name, "w");
	fprintf(file, "%d %d\n", mat_t->m, mat_t->n); //print number of cols and rows
	sp_tuples_node * currenttuplet = mat_t->tuples_head;
	while(currenttuplet!=NULL){ //iterate through the tuples
		fprintf(file, "%d %d %f\n", currenttuplet->row, currenttuplet->col, currenttuplet->value); //print nonzero cell data
		currenttuplet = currenttuplet->next;
	}
	fclose(file);
	return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){
	sp_tuples * matC = malloc(sizeof(sp_tuples)); //allocate memory to the sp_tuples struct
	matC->m = matA->m; //copy over dimensions
	matC->n = matA->n;
	sp_tuples_node * currentNode = matA->tuples_head; //iterate through copying A's contents to C
	while(currentNode != NULL){
		set_tuples(matC, currentNode->row, currentNode->col, currentNode->value);
		currentNode = currentNode->next;
	}
	currentNode = matB->tuples_head; //iterate through copying/adding B's contents to C
	while(currentNode != NULL){
		set_tuples(matC, currentNode->row, currentNode->col, (currentNode->value) + gv_tuples(matC, currentNode->row, currentNode->col));
		currentNode = currentNode->next;
	}
	
	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
	sp_tuples * matC = malloc(sizeof(sp_tuples)); //allocate memory to the sp_tuples struct
	if(matA->n != matB->m){
		return NULL;
	}
	matC->m = matA->m;
	matC->n = matB->n;
	int nz = 0;
	sp_tuples_node * currentAtuplet = matA->tuples_head;
	while(currentAtuplet!=NULL){ //iterate through A's tuples
		sp_tuples_node * currentBtuplet = matB->tuples_head;
		while(currentBtuplet!=NULL){ //iterate through B's tuples
			if(currentAtuplet->col == currentBtuplet->row){
				double value = (currentAtuplet->value)*(currentBtuplet->value)+gv_tuples(matC, currentAtuplet->row, currentBtuplet->col);
				set_tuples(matC, currentAtuplet->row, currentBtuplet->col, value);
				nz++;
			}
			currentBtuplet = currentBtuplet->next;
		}
		currentAtuplet = currentAtuplet->next;
	}
	matC->nz = nz;
    return matC;
}


	
void destroy_tuples(sp_tuples * mat_t){
	sp_tuples_node * pointer = mat_t->tuples_head;
	while(pointer!=NULL){
		sp_tuples_node * nextPointer = pointer->next;
		free(pointer);
		pointer = nextPointer;
	}
	free(mat_t);
    return;
}  






