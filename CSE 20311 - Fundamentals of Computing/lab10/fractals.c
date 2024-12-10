/*
   Will Krzastek
   Lab 10
   Fractals
*/

#include "Graphics/gfx.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <unistd.h>

// because M_PI doesn't like to work even with including math.h
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#define WIDTH 750
#define HEIGHT 750
#define MARGIN 20

void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3);
void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
void shrinkingSquares(int x, int y, int s, int m);
void drawSquare(double x, double y, double size);
void spiralSquares(int x, int y, double angle);
void circularLace(int x, int y, int d);
void snowflake(int x, int y, int l);
void tree(int x, int y, int l, double angle);
void fern(int x, int y, int l, double angle);
void spiralOfSpirals(int x, int y, double s, double t);

int main() 
{
    bool loop = true;
    char c;

    gfx_open(WIDTH, HEIGHT, "Fractal Display");

    while (loop)
    {
        c = gfx_wait();
        gfx_clear();

        switch (c)
        {
            // 1: Sierpinski Triangle
            case '1':
                sierpinski(WIDTH / 2, HEIGHT - MARGIN, MARGIN, MARGIN, WIDTH - MARGIN, MARGIN);
                gfx_flush();
                break;
            
            // 2: Shrinking Squares
            case '2':
                shrinkingSquares(WIDTH / 2, HEIGHT / 2, (WIDTH - MARGIN) / 2, MARGIN);
                gfx_flush();
                break;

            // 3: Spiral Squares
            case '3':
                spiralSquares(WIDTH / 2, HEIGHT / 2, 0);
                gfx_flush();
                break;

            // 4: Circular Lace
            case '4':
                circularLace(WIDTH / 2, HEIGHT / 2, (WIDTH - 2 * MARGIN) / 3);
                gfx_flush();
                break;

            // 5: Snowflake (Koch Snowflake)
            case '5':
            {
                snowflake(WIDTH / 2, HEIGHT / 2, (WIDTH - 2 * MARGIN) / 3);
                gfx_flush();
                break;
            }

            // 6: Tree
            case '6':
                // Make it bigger so top touches near top of the screen:
                tree(WIDTH / 2, HEIGHT - MARGIN, (HEIGHT - 2 * MARGIN) / 3, M_PI/2);
                gfx_flush();
                break;

            // 7: Fern
            case '7':
                fern(WIDTH / 2, HEIGHT - MARGIN, 2 * (HEIGHT - 2 * MARGIN) / 3, M_PI/2);
                gfx_flush();
                break;

            // 8: Spiral of Spirals
            case '8':
                // Try starting bottom-left and going counter-clockwise:
                spiralOfSpirals(WIDTH / 2, HEIGHT / 2, WIDTH / 2, M_PI);
                gfx_flush();
                break;

           case 'q':
                loop = false;
                break;

            default:
                break;
        }
    }

    return 0;
}

// Fractal 1: Sierpinski
void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3)
{
    // base case
    if (abs(x2 - x1) < 5) return;

    // draw triangle
    drawTriangle(x1, y1, x2, y2, x3, y3);

    gfx_flush();
	usleep(1000);

    // recursive calls
    sierpinski(x1, y1, (x1 + x2) / 2, (y1 + y2) / 2, (x1 + x3) / 2, (y1 + y3) / 2);
    sierpinski((x1 + x2) / 2, (y1 + y2) / 2, x2, y2, (x2 + x3) / 2, (y2 + y3) / 2);
    sierpinski((x1 + x3) / 2, (y1 + y3) / 2, (x2 + x3) / 2, (y2 + y3) / 2, x3, y3);
}

void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    gfx_line(x1, y1, x2, y2);
    gfx_line(x2, y2, x3, y3);
    gfx_line(x3, y3, x1, y1);
}

// Fractal 2: Shrinking Squares
void shrinkingSquares(int x, int y, int s, int m)
{
    // Base case: stop if the square size becomes too small
    if (s < 3) return;

    // Draw the current square, centered at (x, y)
    drawSquare(x - s / 2, y - s / 2, s);

    gfx_flush();
    usleep(1000);

    // Recursive calls for squares at each corner with proper spacing
    shrinkingSquares(x - s / 2, y - s / 2, s / 2 - m, m / 2); // Top-left
    shrinkingSquares(x + s / 2, y - s / 2, s / 2 - m, m / 2); // Top-right
    shrinkingSquares(x + s / 2, y + s / 2, s / 2 - m, m / 2); // Bottom-right
    shrinkingSquares(x - s / 2, y + s / 2, s / 2 - m, m / 2); // Bottom-left
}



void drawSquare(double x, double y, double size)
{
    gfx_line(x, y, x+size, y);
    gfx_line(x+size, y, x+size, y+size);
    gfx_line(x+size, y+size, x, y+size);
    gfx_line(x, y+size, x, y);
}

// Fractal 3: Spiral Squares
void spiralSquares(int x, int y, double angle)
{
    // Handle base case with maximum spiral at 20PI
	if (angle > 20 * M_PI) return;


	int x1, y1;

	x1 = x + exp(0.15 * angle) * cos(angle);
	y1 = y - exp(0.15 * angle) * sin(angle);

	// Draw square
	drawSquare(x1, y1, exp(0.1 * angle));

    gfx_flush();
	usleep(50000);

	// Recursively draw squares
	spiralSquares(x, y, angle + M_PI/8);
}

// Fractal 4: Circular Lace
void circularLace(int x, int y, int d)
{
    // Handle base case with minimum diameter 1
	if (d <= 1) return;


	// Draw circle
	gfx_circle(x, y, d);

    gfx_flush();
	usleep(1000);

	int i;
	float theta = M_PI/3;

	// Recursively draw circles in 6-point fashion around circle
	for (i = 0; i < 6; ++i) {
		circularLace(x + d * cos(theta), y + d * sin(theta), d / 3);
		theta += M_PI/3;
	}
}

// Fractal 5: Snowflake (Koch Snowflake)
void snowflake(int x, int y, int l)
{
    // Handle base case with minimum length 1
	if (l < 1) return;

	int i;
	for (i = 0; i < 5; i++)
    {
		gfx_line(x, y, x+l*cos(2*M_PI*i/5), y+l*sin(2*M_PI*i/5));
	}
	gfx_flush();
	usleep(1000);

	// recurses at the end of each line in the pentagonal snowflake
	for (i = 0; i < 5; i++)
    {
		snowflake(x+l*cos(2*M_PI*i/5), y+l*sin(2*M_PI*i/5), l/3);
	}
}


// Fractal 6: Tree
void tree(int x, int y, int l, double angle)
{
    // Handle base case with minimum branch length 2
	if (l <= 2) return;

	int x1, y1, rl;

	x1 = x + l * cos(angle);
	y1 = y - l * sin(angle);

	rl = 7 * l / 10;

	// Draw branch
	gfx_line(x, y, x1, y1);

    gfx_flush();
	usleep(1000);

	// Recursively draw branches, one to each side
	tree(x1, y1, rl, angle + M_PI/6);
	tree(x1, y1, rl, angle - M_PI/6);
}

// Fractal 7: Fern (Simplified symmetrical branching)
void fern(int x, int y, int l, double angle)
{
    // Handle base case with minimum branch length 2
	if (l <= 2) return;

	int i, x1, y1, xstep, ystep, rl, xb, yb;

	x1 = x + l * cos(angle);
	y1 = y - l * sin(angle);
	
	xstep = (x1 - x) / 4;
	ystep = (y - y1) / 4;

	rl = l / 3;

	// Draw branch
	gfx_line(x, y, x1, y1);

    gfx_flush();
	usleep(1000);

	// Recursively draw equidistant branches, four to each side
	for (i = 1; i <= 4; ++i) {
		xb = x + i * xstep;
		yb = y - i * ystep;
		fern(xb, yb, rl, angle + M_PI/5);
		fern(xb, yb, rl, angle - M_PI/5);
	}
}

// Fractal 8: Spiral of Spirals
void spiralOfSpirals(int x, int y, double s, double t)
{
    // base case
    if (s < 1) return;

	// center point
	gfx_point(x, y);
	gfx_flush();
    usleep(10);

	// each rotation
	s -= s/15;
	int xf = x+s*cos(t);
	int yf = y+s*sin(t);
	t += 0.5;

	// recursion
	spiralOfSpirals(xf, yf, s/3, 0);
	spiralOfSpirals(x, y, s, t);
}


