#include <stdio.h>
#include <math.h>
#define M_PI 3.14159265358979323846

int main()
{
    float n;
    float omega1;
    float omega2;
    float i;
    float x_i;
    float f_x_i;
    printf("Enter the values of n, omega1, and omega2 in that order\n");
    scanf("%f %f %f", &n, &omega1, &omega2);
    for(i = 0; i <= n - 1; i ++)
    {
        x_i = i * M_PI / n;
        f_x_i = sin(omega1 * x_i) + .5 * sin(omega2 * x_i);
        printf("(%f, %f)\n", x_i, f_x_i);
    }
    return 0;
}

