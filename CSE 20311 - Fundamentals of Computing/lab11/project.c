#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

int main() 
{
    printf("Welcome to Tic-Tac-Toe!\n");
    printf("You will play against the AI.\n");
    printf("Enter your move as two numbers (row and column) separated by a space.\n\n");

    srand(time(NULL)); // Seed the random number generator

    char humanPlayer, aiPlayer;
    while (1)
    {
        printf("Choose your symbol (X or O): ");
        scanf(" %c", &humanPlayer);

        if (humanPlayer == X || humanPlayer == O)
        {
            aiPlayer = (humanPlayer == X) ? O : X;
            break;
        }
        else
        {
            printf("Invalid choice! Please choose X or O.\n");
        }
    }

    int difficulty = 0;
    while (difficulty < 1 || difficulty > 3)
    {
        printf("Select AI difficulty: 1 (Easy), 2 (Medium), 3 (Hard): ");
        scanf("%d", &difficulty);
    }

    GameState game;
    initializeGame(&game);

    while (!isTerminal(&game))
    {
        displayBoard(&game);

        if (game.currentPlayer == humanPlayer)
        {
            getPlayerMove(&game, humanPlayer); // Pass the human player's symbol
        }
        else
        {
            if (difficulty == 1)
                getAIMoveEasy(&game, aiPlayer);
            else if (difficulty == 2)
                getAIMoveMedium(&game, aiPlayer);
            else
                getAIMoveHard(&game, aiPlayer);
        }
    }

    displayBoard(&game);

    int winner = checkWinner(&game);
    if (winner == humanPlayer)
        printf("%sPlayer %c wins! Congratulations!%s\n", (humanPlayer == X) ? RED : BLUE, humanPlayer, RESET);
    else if (winner == aiPlayer)
        printf("%sPlayer %c (AI) wins! Better luck next time.%s\n", (aiPlayer == X) ? RED : BLUE, aiPlayer, RESET);
    else
        printf("It's a tie! Well played!\n");

    return 0;
}
