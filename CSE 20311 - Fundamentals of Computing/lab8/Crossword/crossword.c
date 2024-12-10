/*
Will Krzastek
Lab 8
Main Crossword Driver
*/

#define LETTERS 16
#define WORDS 20
#define BOARD 15

#include "words.h"

int main(int argc, char *argv[])
{
    srand(time(NULL)); // seed for scrambling clues

    // initialize boards
    char board[BOARD][BOARD];
    char puzzle[BOARD][BOARD];
    char solution[BOARD][BOARD];
    
    for (int i = 0; i < BOARD; i++)
    {
        for (int j = 0; j < BOARD; j++)
        {
            puzzle[i][j] = '#';
            solution[i][j] = '.';
            board[i][j] = ' ';
        }
    }

    // initialize word array
    Word words[WORDS];
    for (int i = 0; i < WORDS; i++)
    {
        // i was having stack overflow issues so i'm explicitly setting all strings to be empty initially, and giving arbitrary values to everything
        memset(words[i].word, '\0', sizeof(words[i].word));
        memset(words[i].clue, '\0', sizeof(words[i].clue));
        words[i].length = 0;
        words[i].x = -1;
        words[i].y = -1;
        words[i].direction = 2;
        words[i].placed = 0;
    }
    int num_words = 0;

    FILE *out = stdout; // default output is stdout, we will change this to a file if argc == 3
    
    // if user entered a text file in command line
    if (argc > 1)
    {
        // open argv[1] and make sure it exists
        FILE *fp = fopen(argv[1], "r");
        if (!fp)
        {
            printf("Error opening file: %s\n", fp);
            return 1;
        }
        // read file and see how many words are in it
        num_words = read_file(fp, words);
        fclose(fp);

        // if user also specified an output file
        if (argc == 3)
        {
            // out is argv[2] instead of stdout now
            out = fopen(argv[2], "w");
            if (!out)
            {
                printf("Error opening file: %s\n", argv[2]);
                return 2;
            }
        }
        // can't enter more than 3 command line arguments
        else if (argc > 3)
        {
            printf("Error, too many command line arguments.\n");
            return 3;
        }
    }
    // interactive mode
    else
    {
        // make curr_word empty for now
        char curr_word[LETTERS] = "";

        while (num_words < WORDS) // enforcing the 20 words max
        {
            printf("Enter a word (Enter . to stop): ");
            scanf("%s", curr_word);
            curr_word[strcspn(curr_word, "\n")] = '\0'; // Remove newline character

            // if the user enters a . just end it immediately
            if (strcmp(curr_word, ".") == 0)
            {
                break; 
            }

            // make sure all chars are letters
            int valid = 1;
            for (int i = 0; i < strlen(curr_word); i++)
            {
                if (!isalpha(curr_word[i]))
                {
                    printf("Error, non-letter is present in the word. Ignoring this word.\n");
                    valid = 0;
                    break;
                }
            }
            // make sure it's between 2-15 letters
            if (strlen(curr_word) < 2 || strlen(curr_word) > 15)
            {
                printf("Error, this word is not between 2-15 letters. Ignoring this word.\n");
                valid = 0;
            }

            // if it's valid, update the word and length to word
            if (valid == 1)
            {
                uppercase(curr_word);
                strcpy(words[num_words].word, curr_word);
                words[num_words].length = strlen(curr_word);
                num_words++;
            }
        }
    }

    // sort words array with qsort
    qsort(words, num_words, sizeof(words[0]), compare);
    
    // place words (this function calls the skipped words too)
    place_words(board, words, num_words, out);

    // upate solution and puzzle arrays based on the new board array
    update_solution_puzzle(board, solution, puzzle);

    // print the solution board and puzzle board to stdout or output file
    fprintf(out, "Solution:\n");
    print_board(solution, out);

    fprintf(out, "Puzzle:\n");
    print_board(puzzle, out);

    // display the clues section
    display_clues(words, num_words, out);

    // if we opened a file, close it
    if (out != stdout)
    {
        fclose(out);
    }

    return 0; // success!
}