/*
Will Krzastek
Lab 7
Header file
*/
#define SIZE 40

void printBoard(char[SIZE][SIZE]);
void addCell(char[SIZE][SIZE], int, int);
void removeCell(char[SIZE][SIZE], int, int);
int numNeighbors(char[SIZE][SIZE], int, int);
void updateBoard(char[SIZE][SIZE], char[SIZE][SIZE]);
void nextIteration(char[SIZE][SIZE], char[SIZE][SIZE]);