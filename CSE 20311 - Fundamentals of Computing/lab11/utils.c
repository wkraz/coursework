#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void initializeGame(GameState *game)
{
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            game->board[i][j] = EMPTY;
        }
    }
    game->currentPlayer = X;
}

void displayBoard(GameState *game)
{
    printf("\n    0     1     2\n"); // Column labels
    printf("  +-----+-----+-----+\n"); // Top border
    for (int i = 0; i < SIZE; ++i)
    {
        printf("%d |", i); // Row label and left border
        for (int j = 0; j < SIZE; ++j)
        {
            if (game->board[i][j] == X)
                printf("  %s%c%s  |", RED, X, RESET); // Red X
            else if (game->board[i][j] == O)
                printf("  %s%c%s  |", BLUE, O, RESET); // Blue O
            else
                printf("  %c  |", EMPTY); // Empty cell
        }
        printf("\n"); // Move to the next row
        if (i < SIZE - 1)
            printf("  +-----+-----+-----+\n"); // Middle border
    }
    printf("  +-----+-----+-----+\n\n"); // Bottom border
}



int checkWinner(GameState *game)
{
    for (int i = 0; i < SIZE; ++i)
    {
        // check rows and columns
        if ((game->board[i][0] == game->board[i][1] && game->board[i][1] == game->board[i][2] && game->board[i][0] != EMPTY) ||
            (game->board[0][i] == game->board[1][i] && game->board[1][i] == game->board[2][i] && game->board[0][i] != EMPTY))
            return game->board[i][i];

    }

    // check diagonals
    if ((game->board[0][0] == game->board[1][1] && game->board[1][1] == game->board[2][2] && game->board[0][0] != EMPTY) ||
        (game->board[0][2] == game->board[1][1] && game->board[1][1] == game->board[2][0] && game->board[0][2] != EMPTY))
        return game->board[1][1];

    return 0;
}

int isTerminal(GameState *game)
{
    // check if someone's won
    if (checkWinner(game) != 0) return 1;

    // check if there's an open cell
    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (game->board[i][j] == EMPTY) return 0; 
        }
    }

    // every cell is full and there's no winner, so game's over
    return 1;
}

void getPlayerMove(GameState *game, char player)
{
    int row, col;

    while (1)
    {
        printf("Enter your move (row and column): ");
        scanf("%d %d", &row, &col);

        if (row >= 0 && row < SIZE && col >= 0 && col < SIZE && game->board[row][col] == EMPTY) 
        {
            game->board[row][col] = player;
            game->currentPlayer = (player == X) ? O : X;
            break;
        }
        else
        {
            printf("Invalid move! Try again.\n");
        }
    }
}

// minimax backtracking
int minimax(GameState *game, int depth, int isMaximizing, char aiPlayer)
{
    char opponent = (aiPlayer == X) ? O : X;
    int winner = checkWinner(game);

    // Base cases
    if (winner == aiPlayer)
        return 1;  // AI wins
    if (winner == opponent)
        return -1; // Opponent wins
    if (isTerminal(game))
        return 0;  // Tie

    if (isMaximizing)
    {
        int maxEval = -1000;

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if (game->board[i][j] == EMPTY)
                {
                    game->board[i][j] = aiPlayer; // AI makes a move
                    int eval = minimax(game, depth + 1, 0, aiPlayer);
                    game->board[i][j] = EMPTY;   // Undo move
                    maxEval = eval > maxEval ? eval : maxEval; // Maximize
                }
            }
        }

        return maxEval;
    }
    else
    {
        int minEval = 1000;

        for (int i = 0; i < SIZE; ++i)
        {
            for (int j = 0; j < SIZE; ++j)
            {
                if (game->board[i][j] == EMPTY)
                {
                    game->board[i][j] = opponent; // Opponent makes a move
                    int eval = minimax(game, depth + 1, 1, aiPlayer);
                    game->board[i][j] = EMPTY;   // Undo move
                    minEval = eval < minEval ? eval : minEval; // Minimize
                }
            }
        }

        return minEval;
    }
}


// easy AI: random move
void getAIMoveEasy(GameState *game, char aiPlayer)
{
    int row, col;

    while (1)
    {
        row = rand() % SIZE;
        col = rand() % SIZE;

        if (game->board[row][col] == EMPTY)
        {
            game->board[row][col] = aiPlayer;
            game->currentPlayer = (aiPlayer == X) ? O : X;
            break;
        }
    }
}


// medium AI: block a player's winning move if they have one, or pick a random move
void getAIMoveMedium(GameState *game, char aiPlayer)
{
    char opponent = (aiPlayer == X) ? O : X;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (game->board[i][j] == EMPTY)
            {
                game->board[i][j] = aiPlayer;
                if (checkWinner(game) == aiPlayer)
                {
                    game->currentPlayer = opponent;
                    return;
                }
                game->board[i][j] = EMPTY;
            }
        }
    }

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (game->board[i][j] == EMPTY)
            {
                game->board[i][j] = opponent;
                if (checkWinner(game) == opponent)
                {
                    game->board[i][j] = aiPlayer;
                    game->currentPlayer = opponent;
                    return;
                }
                game->board[i][j] = EMPTY;
            }
        }
    }

    getAIMoveEasy(game, aiPlayer);
}


// hard AI: use the minimax function to get the best move
void getAIMoveHard(GameState *game, char aiPlayer)
{
    int bestScore = -1000;
    int moveRow = -1, moveCol = -1;
    char opponent = (aiPlayer == X) ? O : X;

    for (int i = 0; i < SIZE; ++i)
    {
        for (int j = 0; j < SIZE; ++j)
        {
            if (game->board[i][j] == EMPTY)
            {
                game->board[i][j] = aiPlayer;
                int score = minimax(game, 0, 0, aiPlayer);
                game->board[i][j] = EMPTY;

                if (score > bestScore)
                {
                    bestScore = score;
                    moveRow = i;
                    moveCol = j;
                }
            }
        }
    }

    game->board[moveRow][moveCol] = aiPlayer;
    game->currentPlayer = opponent;
}
