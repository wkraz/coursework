/*
Will Krzastek
Fund Comp
Lab 3
Multiple Quadratic Formulas
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    double a = 1; // arbitrary value that we'll change before actually using
    double b, c, disc, x1, x2; 

    // while True block -- we'll break it when we meet the condition we want
    while (1)
    {
        // get coefficients from user
        printf("Enter a, b, and c separated by a space: ");
        scanf("%lf %lf %lf", &a, &b, &c);

        // if a == 0, we will break the while True loop and terminate the program
        if (a == 0)
        {
            printf("a = 0, terminating program\n");
            break;
        }

        disc = pow(b, 2.0) - (4 * a * c); // calculate discriminant
        
        // get roots from discriminant (same as last week's code)
        if (disc > 0)
        {
            printf("There are 2 solutions\n");
            x1 = (-b + sqrt(disc)) / (2 * a);
            x2 = (-b - sqrt(disc)) / (2 * a);
            printf("The roots are: %lf, %lf\n", x1, x2);
        }
        else if (disc < 0)
        {
            printf("There are 0 solutions\n");
        }
        else
        {
            printf("There is 1 solution\n");
            x1 = (-b) / (2 * a);
            printf("The root is: %lf\n", x1);
        }
    }


    return 0; // while True loop is broken, so end program
}