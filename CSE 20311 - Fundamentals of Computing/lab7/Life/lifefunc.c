/*
Will Krzastek
Lab 7
Functions file
*/

#include <stdio.h>
#include "lifefunc.h"

#define SIZE 40

// prints a board with the border
void printBoard(char board[SIZE][SIZE])
{
    for (int x = -1; x <= SIZE; x++)
    {
        for (int y = -1; y <= SIZE; y++)
        {
            // if horizontal edge, print -
            if (x == -1 || x == SIZE)
                printf("-");
            // if vertical edge, print |
            else if (y == -1 || y == SIZE)
                printf("|");
            // not edge, so print X or ' ' respectively
            else
                printf("%c", board[x][y]);
        }
        printf("\n");
    }
}

// adds a cell at a given position - by turning it into an X
void addCell(char board[SIZE][SIZE], int x, int y)
{
    board[x][y] = 'X';
}

// removes a cell at a given position - by making it empty
void removeCell(char board[SIZE][SIZE], int x, int y)
{
    board[x][y] = ' ';
}

// find the number of alive cells for a given position
int numNeighbors(char board[SIZE][SIZE], int x, int y)
{
    // see if it's an edge and account for it to get all the neighbors
    int xmin, xmax, ymin, ymax;
    xmin = x == 0 ? 0 : x - 1;
    ymin = y == 0 ? 0 : y - 1;
    xmax = x == SIZE - 1 ? SIZE - 1 : x + 1;
    ymax = y == SIZE - 1 ? SIZE - 1 : y + 1;

    // loop through neighbors and count how many are alive
    int count = 0;
    for (int i = xmin; i <= xmax; i++)
    {
        for (int j = ymin; j <= ymax; j++)
        {
            if (i == x && j == y) continue; // skip the cell 
            if (board[i][j] == 'X') count++;
        }
    }

    return count;
}

// updates the second board argument to be equal to the first
void updateBoard(char a[SIZE][SIZE], char b[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            b[i][j] = a[i][j];
        }
    }
}

// advances to the next iteration by the rules of the game
void nextIteration(char board[SIZE][SIZE], char next[SIZE][SIZE])
{
    int neighbors;
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            neighbors = numNeighbors(board, i, j); // get number of neighbors

            // apply game of life rules
            if (board[i][j] == 'X')
            {
                // if 2-3 neighbors stay alive, else die
                if (neighbors == 2 || neighbors == 3)
                    next[i][j] = 'X';
                else
                    next[i][j] = ' ';
            }
            else
            {
                // dead cell with 3 neighbors becomes alive
                if (neighbors == 3)
                    next[i][j] = 'X';
                else
                    next[i][j] = ' ';
            }
        }
    }
}