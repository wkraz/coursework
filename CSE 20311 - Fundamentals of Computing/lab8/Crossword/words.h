/*
Will Krzastek
Lab 8
Crossword Function Prototype file
*/

#define WORDS 20
#define LETTERS 16
#define BOARD 15

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

// word struct that we'll use for basically everything
typedef struct {
    char word[LETTERS];
    char clue[LETTERS];
    int x; // starting x pos
    int y; // starting y pos
    int length; 
    int placed; // store 1 if placed in puzzle, 0 if not (so we can backtrack at the end)
    int direction; // 0 across, 1 down, 2 for no direction
} Word;

// linked list node we'll need for the skipped words
typedef struct Node {
    Word word;
    struct Node *next;
} Node;

// prototypes
void print_board(char[BOARD][BOARD], FILE*);
int read_file(FILE *, Word[WORDS]);
void uppercase(char[LETTERS]);
int compare(const void *, const void *);
void place_center(char[BOARD][BOARD], Word*);
int can_place(char[BOARD][BOARD], Word*, int, int, int, int);
void place(char[BOARD][BOARD], Word*, int, int, int, int);
Node* skip(Node*, Word, FILE*);
int place_skip(char[BOARD][BOARD], Word[], Node**, int*, FILE*);
void place_words(char[BOARD][BOARD], Word[], int, FILE*);
void scramble_word(Word*);
void display_clues(Word[], int, FILE*);
void update_solution_puzzle(char[BOARD][BOARD], char[BOARD][BOARD], char[BOARD][BOARD]);