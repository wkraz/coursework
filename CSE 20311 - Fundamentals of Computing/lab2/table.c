/*
Will Krzastek
Fund Comp
Lab 2
Multiplication Table from user input
*/

#include <stdio.h>

int main()
{
    int x, y;
    printf("Enter the size of the x and y axes: ");
    scanf("%d %d", &x, &y);

    // get the length (width) and height of the table -- used in for loops later
    int length = 5 * x + 3;
    int height = y + 2;

    // print top row
    printf("*  "); // everything is 4 spaces apart except the initial *
    for (int i = 1; i <= x; i++)
    {
        printf("    %d", i);
    }

    // print second row -- the ----- bar
    printf("\n");
    printf("   ");
    for (int i = 4; i <= length; i++)
    {
        printf("-");
    }
    printf("\n");

    // loop through every row
    for (int row = 1; row <= y; row++)
    {
        // print left column
        printf("%d |", row);

        // print each row * col entry with spaces in between
        for (int col = 1; col <= x; col++)
        {
            printf("%5d", row * col);
        }
        printf("\n");
    }

    return 0;
}