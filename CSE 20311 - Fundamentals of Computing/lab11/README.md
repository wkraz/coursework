# AI Tic-Tac-Toe Solver

## Introduction
I created a tic-tac-toe bot to play tic-tac-toe against. There are 3 difficulties: easy, medium, hard. The user gets to choose if they want to be X or O, and the AI assumes the other symbol. X is color-coded as red and O is color-coded as blue to make it more visually appealing and easy to understand. 

### Easy Difficulty
Easy difficulty simply chooses a random moves from the available squares. 

### Medium Difficulty
Medium difficulty makes the most "obvious" move. If it can win in one move (2 in a row), it makes that move. If the opponent can win on their next turn, 
it blocks them. If neither of these are met, it just calls AIMoveEasy() and chooses a random move.

### Hard Difficulty
Hard difficulty is unbeatable. I created a minimax algorithm that calls itself recursively to get the best move. It classifies wins for X as 1, and wins for 
O as -1. Thus, it returns the most "optimal" move i.e. the one that leads to either the max outcome or min outcome, depending on who the AI is playing as. 
It is a pretty simple backtracking algorithm that uses DFS to basically run through every possible move to see the most optimal one. One assumption it does make is that the opponent (the player in this case) always makes the optimal move, which isn't always the case due to human error.
Since the AI always makes the optimal move, it will never lose and the result will always be a loss/tie for the player. 

## Code Structure
I divided my code into 3 files: 
- project.c - main runner
- utils.c - function file
- utils.h - header file w/ struct definition

## How I followed the Requirements
I created a GameState struct that had 2 qualities: 2d char array that represents the board, and a char that represents whose move it is: X or O. I didn't use any global variables, besides from defining some variables to make my code more readable (especially for the colors, no way I am typing out "\033[1;31m" whenever I want to use blue, lol). It has a makefile that compiles everything. It is pretty efficient, though the minimax function could be improved to use alpha-beta pruning to stop searching when we find a route that leads to 1 or -1 (respectively), but due to how small the board is (3x3), this wasn't necessary in my opinion as it wouldn't really improve the efficiency in a meaningful way. I didn't use gfx, as I didn't think it would make this project better in a meaningful way, as it's just tic-tac-toe.  