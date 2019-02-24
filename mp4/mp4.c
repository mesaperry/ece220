/*
This program was created by Mesa Perry, borrowing
an algorithm for the print_semiprimes function.
The function is_prime returns whether the input
integer is prime or not. The function
print_semiprimes prints all semiprimes within the
input range, [a, b], and returns 1 if any
semiprimes were found, 0 if not. The body of this
program uses these functions to ask the user for
a range, then prints out the respective semiprimes
*/
 
#include <stdio.h>
 
int is_prime(int number) /*check if input is prime*/
{
    int count = 0; /*used to keep track of number of multiples*/
    for (int i = 1; i <= number; i ++) /*first possible multiple*/
    {
        for (int j = 1; j <= i; j ++) /*second possible multiple*/
        {
            if (i * j == number) /*check all unique multiples*/
            {
                count ++;
            }
        }
    }
    if (count == 1)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
int print_semiprimes(int a, int b) /*print all semiprimes in range*/
{
    int exists = 0; /*keep track if any semiprimes exists*/
    for (int n = a; n <=b; n ++) /*loop through possible semiprimes in range*/
    {
        for (int k = 2; k <= n-1; k ++) /*loop through factors of possible semiprimes*/
        {
            if (n % k == 0 && is_prime(k) && is_prime(n/k)) /*print if the two respective factors are prime*/
            {
                printf("%u ", n);
                exists ++;
                break; /*avoid triggering off of multiple prime factors*/
            }
        }
    }
    if (exists > 0)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}
 
int main()
{
    int a, b;
    printf("Input two numbers: ");
    scanf("%u %u", &a, &b);
    print_semiprimes(a, b);
    return 0;
}
