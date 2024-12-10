/*
Will Krzastek
Lab 7
Main driver
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "lifefunc.h"

#define SIZE 40

int main(int argc, char *argv[])
{
    // read input file if present
    FILE *file;
    if (argc == 2)
    {
        file = fopen(argv[1], "r");
    }
    // can only have 1 additional command line argument
    else if (argc > 2)
    {
        printf("Error. Too many command line arguments\n");
        return 1;
    }

    // initialize present and future boards (make them empty)
    char board[SIZE][SIZE];
    char next[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            board[i][j] = ' ';
            next[i][j] = ' ';
        }
    }

    printBoard(board); // print initial empty board
    // handle user input (both interactive and command line mode)
    while (1)
    {
        // take user input for each move
        char line[8]; // 8 is longest it can be: letter arg (1) space (2) int > 9 (4) space (5) int > 9 (7) null (8)
        // if no arg, read from stdin
        if (!file)
            fgets(line, 8, stdin);
        // if argv, read from the file
        else
            fgets(line, 8, file);
        
        char o = line[0]; // argument
        int x, y;
        sscanf(line, "%c %d %d", &o, &x, &y); // get ints from line

        switch(o)
        {
            // adding a cell
            case 'a':
                system("clear");
                addCell(next, x, y);
                updateBoard(next, board);
                printBoard(board);
                break;

            // removing a cell
            case 'r':
                system("clear");
                removeCell(next, x, y);
                updateBoard(next, board);
                printBoard(board);
                break;
            
            // next iteration
            case 'n':
                system("clear");
                nextIteration(board, next);
                updateBoard(next, board);
                printBoard(board);
                break;
            
            // quiting program
            case 'q':
                return 1;
                break;
            
            // running the game until it ends
            case 'p':
                while (1)
                {
                    usleep(20000); // delay between iterations (change between 0.2 s and 0.02 s for testing and running)
                    system("clear"); // get rid of previous board

                    // go to next board by rules of game, update board to the next board and print it
                    nextIteration(board, next);
                    updateBoard(next, board);
                    printBoard(board);
                }
                break;
        }
    }  

    return 0;
}