/*
Will Krzastek
Fund Comp
Lab 1
Formula for the volume of a cone
*/

#include <stdio.h>
#include <math.h>

int main(void)
{
    printf("Formula for the volume of a cone.\n");
    // Initialize variables
    double r, h, volume;
    double PI = 3.14;

    // Get user input
    printf("Enter the radius (m): ");
    scanf("%lf", &r);

    printf("Enter the height (m): ");
    scanf("%lf", &h);

    // Calculate volume and display it to the user
    volume = PI * pow(r, 2.0) * (h / 3.0);
    printf("The volume of the cone is %.3lf m^3.\n", volume);
}