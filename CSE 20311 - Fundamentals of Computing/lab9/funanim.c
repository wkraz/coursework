#include "Graphics/gfx.h"
#include <math.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

#define PI 3.14159265358979323846
#define NUM_SHAPES 3

void draw_circle(int x, int y, int radius);
void draw_square(int x, int y, int size);
void draw_triangle(int x, int y, int size);

int main()
{
    int width = 800, height = 600;
    int centerX = width / 2, centerY = height / 2;   // center of rotation
    double angle = 0.0;                              // current rotation angle
    double speed = 0.05;                             // rotation speed (radians per frame)
    int radius = 100;                                // distance of shapes from center
    int running = 1;                                 // animation state (1 = running, 0 = stopped)
    int clockwise = 1;                               // rotation direction (1 = clockwise, -1 = counterclockwise)

    gfx_open(width, height, "Rotating Animation");
    srand(time(NULL)); // seed for random colors

    while (1)
    {
        // check for user input
        if (gfx_event_waiting())
        {
            int event = gfx_wait();
            // quit if they enter 'q'
            if (event == 'q')
            {
                break;
            }
            else if (event == 'c')
            {
                clockwise = -clockwise;     // flip rotation direction
            }
            else if (event == 's')
            {
                running = !running;         // flip animation state
            }
        }

        if (running)
        {
            // clear the screen
            gfx_clear();

            // calculate positions of shapes
            for (int i = 0; i < NUM_SHAPES; ++i)
            {
                double currentAngle = angle + i * 2 * PI / NUM_SHAPES;    // spread them evenly
                int x = centerX + radius * cos(currentAngle);
                int y = centerY + radius * sin(currentAngle);

                // set random colors for each shape
                gfx_color(rand() % 256, rand() % 256, rand() % 256);

                if (i % 3 == 0)
                {
                    draw_circle(x, y, 30);
                }
                else if (i % 3 == 1)
                {
                    draw_square(x, y, 40);
                }
                else
                {
                    draw_triangle(x, y, 50);
                }
            }

            gfx_flush();

            // update angle
            angle += speed * clockwise;

            // sleep for smooth animation at ~60 fps
            usleep(16000);
        }
    }

    return 0;
}

// draw a circle (same as in symbol.c)
void draw_circle(int x, int y, int radius)
{
    for (double theta = 0; theta < 2 * PI; theta += 0.01)
    {
        int x1 = x + radius * cos(theta);
        int y1 = y + radius * sin(theta);
        gfx_point(x1, y1);
    }
}

// draw a square
void draw_square(int x, int y, int size)
{
    int half = size / 2;
    gfx_line(x - half, y - half, x + half, y - half);
    gfx_line(x + half, y - half, x + half, y + half);
    gfx_line(x + half, y + half, x - half, y + half);
    gfx_line(x - half, y + half, x - half, y - half);
}

// draw a triangle
void draw_triangle(int x, int y, int size)
{
    int half = size / 2;
    gfx_line(x, y - half, x - half, y + half);
    gfx_line(x - half, y + half, x + half, y + half);
    gfx_line(x + half, y + half, x, y - half);
}