/*
Will Krzastek
Fund Comp
Lab 3
Quadrants and Polar Coordinates
*/

#include <stdio.h>
#include <math.h>

const double PI = 3.1415926535; // define pi because M_PI acts weirdly sometimes

// function prototypes
int get_quadrant(double x, double y);
double get_radius(double x, double y);
double get_angle(double x, double y);
void show_info(int quad, double x, double y);


int main(void)
{
    // get x and y from user
    double x, y;
    printf("Enter the x and y coordinates, separated by a space: ");
    scanf("%lf%lf", &x, &y);

    // get quadrant, radius, and angle from user functions, then show info
    int quad = get_quadrant(x, y);
    double radius = get_radius(x, y);
    double angle = get_angle(x, y);
    show_info(quad, radius, angle);

    return 0; // exit program successfully
}

int get_quadrant(double x, double y)
{
    // first quadrant
    if (x >= 0 && y >= 0)
    {
        return 1;
    }
    // second
    else if (x < 0 && y >= 0)
    {
        return 2;
    }
    // third
    else if (x < 0 && y < 0)
    {
        return 3;
    }
    // fourth
    else
    {
        return 4;
    }
}

double get_radius(double x, double y)
{
    // distance formula
    return (sqrt(pow(x, 2.0) + pow(y, 2.0)));
}

double get_angle(double x, double y)
{
    // use atan2 because it accounts for the quadrants better than atan
    return (atan2(y, x) * 180 / PI); // radians --> degrees so multiply by 180 divide by pi
}

void show_info(int quad, double radius, double angle)
{
    // print quadrant, radius, and angle to user
    printf("Quadrant = %d\nRadius = %.2lf\nAngle = %.2lf\n", quad, radius, angle);
}