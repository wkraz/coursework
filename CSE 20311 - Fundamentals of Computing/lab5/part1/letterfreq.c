/*
Will Krzastek
Fund Comp
Lab 5
Letter Frequency
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define LETTERS 26

void display_info(int, int, int [], char []);

int main(void)
{
    // initialize variables
    char infile[30];
    int letters[LETTERS];
    int char_count, letter_count = 0;
    FILE *file;

    // get file name from user
    printf("Enter a file name: ");
    scanf("%s", infile);

    // open file and make sure it's not null
    file = fopen(infile, "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    // set every element of letter array to 0
    for (int i = 0; i < LETTERS; i++)
    {
        letters[i] = 0;
    }

    int c;
    while ((c = getc(file)) != EOF)
    {
        // if c is uppercase, make it lowercase
        if (c >= 65 && c <= 90)
        {
            c += 32;
        }

        // check if it's a letter
        if (c >= 97 && c <= 122)
        {
            c -= 97; // a = 97 --> a = 0 so we can index

            letters[c]++; // count element + 1
            letter_count++; // letter count + 1
        }
        char_count++; // character count + 1
    }

    // call user defined function to display info about the file
    display_info(letter_count, char_count, letters, infile);

    // close file and return w/ successful code
    fclose(file);
    return 0;
}

void display_info(int letter_count, int char_count, int letters[], char infile[])
{
    printf("\n");

    // print total letters & chars
    printf("General summary for %s\n", infile);
    printf("  there were %d total characters\n", char_count);
    printf("  there were %d total letters\n\n", letter_count);

    // print how many of each letter
    printf("Letter counts: \n");
    for (int i = 0; i < LETTERS; i++)
    {
        // every 6 letters print new line
        if ((i % 6 == 0) && i != 0)
        {
            printf("\n");
        }
        // print the index + 97 (a = 0 --> a = 97) to print letter, convert to char
        // then print the count variable in each index
        printf("%3c: %6d", (char) (i + 97), letters[i]);
    }

    printf("\n\n");

    printf("Letter percentages: \n");
    for (int i = 0; i < LETTERS; i++)
    {
        // every 6 letters print new line
        if ((i % 6 == 0) && i != 0)
        {
            printf("\n");
        }
        // same as letter count but divide by letter count and multiply by 100
        printf("%3c: %4.1lf%%", (char)(i + 97), ((double) letters[i] / letter_count) * 100);
    }
    printf("\n");
}