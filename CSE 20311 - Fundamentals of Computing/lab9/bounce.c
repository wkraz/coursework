#include "Graphics/gfx.h"
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <math.h>

#define PI 3.14159265358979323846

void update_position(int *x, int *y, int *vx, int *vy, int width, int height, int radius);
void randomize_velocity(int *vx, int *vy);

int main()
{
    int width = 800, height = 600;
    int radius = 20;                    // ball radius
    int x = width / 2, y = height / 2;  // initial position of the ball (middle of screen)
    int vx = 4, vy = 3;                 // initial velocities (random constants)

    gfx_open(width, height, "Bouncing Ball");
    srand(time(NULL));                  // seed for random number generator

    while (1)
    {
        // check for user input w/ gfx function
        if (gfx_event_waiting())
        {
            int event = gfx_wait();
            // quit if they enter 'q'
            if (event == 'q')
            {
                break; 
            }
            // if left mouse click, update position to the mouse click
            else if (event == 1) 
            {
                x = gfx_xpos();
                y = gfx_ypos();
                randomize_velocity(&vx, &vy);       // Assign a new random velocity
            }
        }

        // Update ball position
        update_position(&x, &y, &vx, &vy, width, height, radius);

        // clear the screen and draw the ball
        gfx_clear();
        gfx_color(255, 0, 0);       // red
        gfx_circle(x, y, radius);

        gfx_flush();

        // sleep for a smooth animation ~60 fps (1 second / 60 frames = 16.67 ms = 1600 us)
        usleep(16000);
    }

    return 0;
}

// function to update ball position and handle wall collisions
void update_position(int *x, int *y, int *vx, int *vy, int width, int height, int radius)
{
    // update x and y by velocities (by reference)
    *x += *vx;
    *y += *vy;

    // bounce off left or right walls
    if (*x - radius <= 0 || *x + radius >= width)
    {
        *vx = -*vx;                                         // reverse velocity in x direction
        *x = (*x - radius <= 0) ? radius : width - radius; // prevent sticking
    }

    // bounce off top or bottom walls
    if (*y - radius <= 0 || *y + radius >= height)
    {
        *vy = -*vy;                                          // reverse velocity in y direction
        *y = (*y - radius <= 0) ? radius : height - radius; // prevent sticking
    }
}

// function to assign a random velocity
void randomize_velocity(int *vx, int *vy)
{
    int speed = rand() % 5 + 2; // random speed between 2 and 6
    double angle = (double)(rand() % 360) * PI / 180.0; // random angle in radians

    *vx = (int)(speed * cos(angle));
    *vy = (int)(speed * sin(angle));

    // ensure velocity isn't zero
    if (*vx == 0) *vx = (rand() % 2 == 0) ? 1 : -1;
    if (*vy == 0) *vy = (rand() % 2 == 0) ? 1 : -1;
}