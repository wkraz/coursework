#include "Graphics/gfx.h"
#include <math.h>
#include <stdlib.h>

#define SIZE 50
#define PI 3.14159265358979323846

void draw_square(int x, int y, int size);
void draw_circle(int x, int y, int size);
void draw_triangle(int x, int y, int size);
void draw_polygon(int x, int y, int size, int sides);

int main()
{
    // initialize our board
    int width = 800, height = 600;
    gfx_open(width, height, "Symbolic Typewriter");

    while (1)
    {
        // use gfx functions to see what's happening
        int event = gfx_wait();
        int x = gfx_xpos();
        int y = gfx_ypos();

        // if users presses 'q' quit the program
        if (event == 'q')
        {
            break;
        }

        switch (event)
        {
        case 1: // left mouse click
            gfx_color(0, 0, 255); // Blue
            draw_square(x, y, SIZE);
            break;
        case 'c': // Letter 'c'
            gfx_color(255, 255, 255); // White
            draw_circle(x, y, SIZE);
            break;
        case 't': // Letter 't'
            gfx_color(0, 255, 0); // Green
            draw_triangle(x, y, SIZE);
            break;
        case 27: // ESC key
            gfx_clear();
            break;
        default:
            if (event >= '3' && event <= '9') // polygons with n = 3-9 sides
            {
                gfx_color(128, 0, 128); // Purple
                draw_polygon(x, y, SIZE, event - '0');
            }
            break;
        }
    }

    return 0;
}

// function to draw a square
void draw_square(int x, int y, int size)
{
    int half = size / 2;   // get halfway point of square
    // draw all 4 lines of a square by gfx rules
    gfx_line(x - half, y - half, x + half, y - half);
    gfx_line(x + half, y - half, x + half, y + half);
    gfx_line(x + half, y + half, x - half, y + half);
    gfx_line(x - half, y + half, x - half, y - half);
}

// function to draw a circle
void draw_circle(int x, int y, int size)
{
    int radius = size / 2;   // r = d / 2
    // draw the circle by rotating (polar coords)
    for (double theta = 0; theta < 2 * PI; theta += 0.01)
    {
        int x1 = x + radius * cos(theta);
        int y1 = y + radius * sin(theta);
        gfx_point(x1, y1);
    }
}

// function to draw a triangle
void draw_triangle(int x, int y, int size)
{
    int half = size / 2;
    // draw 3 lines of triangle
    gfx_line(x, y - half, x - half, y + half);
    gfx_line(x - half, y + half, x + half, y + half);
    gfx_line(x + half, y + half, x, y - half);
}

// function to draw a polygon
void draw_polygon(int x, int y, int size, int sides)
{
    // use polar coords to draw it since we don't know how many sides we'll have
    double radius = size / 2.0;
    double angle_step = 2 * PI / sides;

    // draw n number of sides
    for (int i = 0; i < sides; ++i)
    {
        double angle1 = i * angle_step;
        double angle2 = (i + 1) * angle_step;
        int x1 = x + radius * cos(angle1);
        int y1 = y + radius * sin(angle1);
        int x2 = x + radius * cos(angle2);
        int y2 = y + radius * sin(angle2);
        gfx_line(x1, y1, x2, y2);
    }
}