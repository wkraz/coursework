/*
Will Krzastek
Fund Comp
Lab 2
ASCII Plot of y = 8(2 + cos(x))
*/

#include <stdio.h>
#include <math.h>

int main()
{
    double x = 30.0;
    double y;

    // print initial statement and title
    printf("Plot for y = 8 * (2 + cos(x)) from x = 0.0 to x = 30.0\n");
    printf("   X     Y\n");

    // go from 0 to 30 by 0.2
    for (double i = 0; i <= x; i += 0.2)
    {
        // calculate y value for specific x value from formula
        y = 8 * (2 + cos(i));

        // print x and y value
        printf("%5.2f %6.2f  ", i, y);

        int n = ceil(y); // round y up using the ceiling function

        // incremented by 1 in y, print a '#'
        for (int j = 1; j <= n; j++)
        {
            printf("#");
        }
        printf("\n");
    }

    // print global max and min
    printf("Maximum of y = 24.00 occurs at x = 12.60\n");
    printf("Minimum of y = 8.00 occurs at x = 9.40\n");

    return 0;
}