/*         
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */

/* These three functions were written by Mesa Perry. The set_seed
function is used to create a seed for future use with the function
rand(). The start_game() function initializes the game by creating
four random numbers which become the solution. The make_guess()
function takes an input guess string and prints the number of
perfect and misplaced matches. This file is meant to be used in
conjunction with main.c to create the main structure of the game.
*/

 
#include <stdio.h>
#include <stdlib.h>
 
//#include "prog5.h"
 

static int guess_number;
static int solution1;
static int solution2;
static int solution3;
static int solution4;
 
 
/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid.
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */

int
set_seed (const char seed_str[])
{
    int seed;
    char post[1];
    if (sscanf(seed_str, "%d%1s", &seed, post) == 1)
    {
        srand(seed);
        return 1;
    }
    else
    {
        printf("set_seed: invalid seed\n");
        return 0;
    }
    return 0;
} 

/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above.
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 * INPUTS: none
 * OUTPUTS: *one -- the first solution value (between 1 and 8)
 *          *two -- the second solution value (between 1 and 8)
 *          *three -- the third solution value (between 1 and 8)
 *          *four -- the fourth solution value (between 1 and 8)
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */

void
start_game (int* one, int* two, int* three, int* four)
{
    //your code here
    *one = rand() % 8 + 1; //set each digit to a random number between 1 and 8
    *two = rand() % 8 + 1;
    *three = rand() % 8 + 1;
    *four = rand() % 8 + 1;
    guess_number = 1;
    solution1 = *one; //make copies
    solution2 = *two;
    solution3 = *three;
    solution4 = *four;
}
 
/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str.
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 integers, within the range 1-8). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: the following are only valid if the function returns 1 (A valid guess)
 *          *one -- the first guess value (between 1 and 8)
 *          *two -- the second guess value (between 1 and 8)
 *          *three -- the third guess value (between 1 and 8)
 *          *four -- the fourth color value (between 1 and 8)
 * RETURN VALUE: 1 if the guess string is valid (the guess contains exactly four
 *               numbers between 1 and 8), or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess)
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int
make_guess (const char guess_str[], int* one, int* two, int* three, int* four)
{
	int w, x, y, z;
    char post[1];
    int perfect = 0, misplaced = 0;
    int onemark = 0, twomark = 0, threemark = 0, fourmark = 0, sol1mark = 0, sol2mark = 0, sol3mark = 0, sol4mark = 0;
    if (sscanf(guess_str, "%d%d%d%d%1s", &w, &x, &y, &z, post) == 4)
    { //check that only four numbers are entered
		if (1<=w && w<=8 && 1<=x && x<=8 && 1<=y && y<=8 && 1<=z && z<=8)
		{ //check that the four numbers are all between 1 and 8
			*one = w; //I used the wrong variables here,
			*two = x; //and I'm lazy so I'm just gonna
			*three = y; //set the guess variables to the right
			*four = z; //numbers so it outputs correctly
		    if (w == solution1) //Here is perfect match logic
		    {
		        perfect ++;
		        onemark = 1;
		        sol1mark = 1;
		    }
		    if (x == solution2)
		    {
		        perfect ++;
		        twomark = 1;
		        sol2mark = 1;
		    }
		    if (y == solution3)
		    {
		        perfect ++;
		        threemark = 1;
		        sol3mark = 1;
		    }
		    if (z == solution4)
		    {
		        perfect ++;
		        fourmark = 1;
		        sol4mark = 1;
		    }
		   
		    if (!onemark) //Here is misplaced match logic
		    {
		        if (w == solution2 && !sol2mark)
		        {
		            misplaced ++;
		            onemark = 1;
		            sol2mark = 1;
		        }
		        else if (w == solution3 && !sol3mark)
		        {
		            misplaced ++;
		            onemark = 1;
		            sol3mark = 1;
		        }
		        else if (w == solution4 && !sol4mark)
		        {
		            misplaced ++;
		            onemark = 1;
		            sol4mark = 1;
		        }
		    }
		    if (!twomark)
		    {
		        if (x == solution1 && !sol1mark)
		        {
		            misplaced ++;
		            twomark = 1;
		            sol1mark = 1;
		        }
		        else if (x == solution3 && !sol3mark)
		        {
		            misplaced ++;
		            twomark = 1;
		            sol3mark = 1;
		        }
		        else if (x == solution4 && !sol4mark)
		        {
		            misplaced ++;
		            twomark = 1;
		            sol4mark = 1;
		        }
		    }
		    if (!threemark)
		    {
		        if (y == solution2 && !sol2mark)
		        {
		            misplaced ++;
		            threemark = 1;
		            sol2mark = 1;
		        }
		        else if (y == solution1 && !sol1mark)
		        {
		            misplaced ++;
		            threemark = 1;
		            sol1mark = 1;
		        }
		        else if (y == solution4 && !sol4mark)
		        {
		            misplaced ++;
		            threemark = 1;
		            sol4mark = 1;
		        }
		    }
		    if (!fourmark)
		    {
		        if (z == solution2 && !sol2mark)
		        {
		            misplaced ++;
		            fourmark = 1;
		            sol2mark = 1;
		        }
		        else if (z == solution3 && !sol3mark)
		        {
		            misplaced ++;
		            fourmark = 1;
		            sol3mark = 1;
		        }
		        else if (z == solution1 && !sol1mark)
		        {
		            misplaced ++;
		            fourmark = 1;
		            sol1mark = 1;
		        }
		    }
		    printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect, misplaced);
		    guess_number ++; //go to next guess
		}
   	 	else
    	{
     		printf("make_guess: invalid guess\n"); //exit condition for invalid inputs
      		return 0;
    	}
    }
    else
    {
        printf("make_guess: invalid guess\n"); //another exit condition bc there were two if conditions
        return 0;
    }
    return 1;
}
