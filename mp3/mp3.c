/* This program was written by Mesa Perry. The goal is
to print a specific line of Pascal's Triangle. It
prompts the user to enter a row index, then prints
the line corresponding to the inputted row index.
This program is intended to work for rows 40 or less */

#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n; /* initialize targeted row index */
    int k; /* initialize targeted coefficient */
    printf("Enter the row index : ");
    scanf("%u", &n);
    for(k = 0; k <= n; k ++) /* loop through all coefficients in the line */
    {
        int i;
        unsigned long cof; /* total of all products */
        cof = 1;
        for(i = 1; i <= k; i ++) /* loop through multiplications required to calculate coeffcient */
        {
            cof *= (n + 1 - i);
            cof /= i;
        }
        printf("%lu ", cof); /* print coefficient */
    }
    return 0;
}

