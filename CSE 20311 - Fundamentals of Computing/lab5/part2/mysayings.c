/*
Will Krzastek
Fund Comp
Lab 5
Sayings Manager
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SAYINGS 50
#define MAX_LENGTH 256

// function prototypes
void printMenu(void);
int loadSayings(char [][MAX_LENGTH], char*);
void displaySayings(char [][MAX_LENGTH], int);
void addSaying(char [][MAX_LENGTH], int*);
void searchSaying(char [][MAX_LENGTH], int);
void saveSayings(char [][MAX_LENGTH], int);
void randomSaying(char [][MAX_LENGTH], int);
void every_n_saying(char [][MAX_LENGTH], int);
void is_duplicate(char [][MAX_LENGTH], int);

int main(void)
{
    char sayings[MAX_SAYINGS][MAX_LENGTH]; // 2d char array 
    int count = 0;

    // get the file name from the user
    char filename[31];
    printf("Enter the file name: ");
    scanf("%30s", filename); // read file name from keyboard max 30 chars

    // make sure there are sayings in the file -- return with error if not
    count = loadSayings(sayings, filename);
    if (count == -1)
    {
        return 1; // exit with failure code if we couldn't open file (-1 is error in the function)
    }

    int choice = -1; // arbitrary value of choice that won't conflict w/ condition: != 8

    // while loop that runs until user exits (presses 8)
    while (choice != 8)
    {
        printMenu(); // print users choices

        // get user input and store in an int choice
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // switch statement that runs appropriate function based on choice
        switch (choice)
        {
            case 1:
                displaySayings(sayings, count);
                break;
            case 2:
                addSaying(sayings, &count);
                break;
            case 3:
                searchSaying(sayings, count);
                break;
            case 4:
                saveSayings(sayings, count);
                break;
            case 5:
                randomSaying(sayings, count);
                break;
            case 6:
                every_n_saying(sayings, count);
                break;
            case 7:
                is_duplicate(sayings, count);
                break;
            case 8:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Try again!\n");
        }
    }

    return 0; // successful return code once while loop is exited
}

void printMenu(void)
{
    printf("\nMenu: \n");
    printf("1. Display all sayings\n");
    printf("2. Enter a new saying\n");
    printf("3. List all of the sayings that contain a substring\n");
    printf("4. Save all sayings to a new text file\n");
    printf("5. Display a random saying from the file\n");
    printf("6. Display every 'n' sayings from the file\n");
    printf("7. See if there is a duplicate saying in the file\n");
    printf("8. Quit\n");
}


int loadSayings(char sayings[MAX_SAYINGS][MAX_LENGTH], char* filename)
{
    // open file and make sure it's not null
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return -1;
    }

    // go through file and check how many sayings are inside
    int i = 0;
    // reading line from file into the sayings array
    // goes until we get to max_sayings or read an empty line
    while (fgets(sayings[i], MAX_LENGTH, file) != NULL && i < MAX_SAYINGS)
    {
        sayings[i][strcspn(sayings[i], "\n")] = '\0'; // replacing new line with null character to end each saying
        i++; // increment sayings counter by 1
    }

    fclose(file); // close file once we're done

    return i; // return sayings counter
}

void displaySayings(char sayings[MAX_SAYINGS][MAX_LENGTH], int count)
{
    printf("\nSayings in the database: \n");

    // print every saying in the database
    for (int i = 0; i < count; i++)
    {
        printf("%d. %s\n", i+1, sayings[i]);
    }
}

void addSaying(char sayings[MAX_SAYINGS][MAX_LENGTH], int* count) // pass by reference so we can increment count by 1 at the end 
{
    // see if we're at the max # of sayings
    if (*count >= MAX_SAYINGS)
    {
        printf("Error. Database is full cannot add any more sayings\n");
        return;
    }

    // Get input from user
    printf("Enter a new saying: ");
    char saying[MAX_LENGTH];

    getchar(); // clear input buffer to prevent \n issues 

    fgets(saying, MAX_LENGTH, stdin); // read input into saying (better than scanf because there's probably spaces in this input)
    saying[strcspn(saying, "\n")] = '\0'; // remove new line if fgets captures it

    // add the new copy into the sayings array
    strcpy(sayings[*count], saying); 

    // dereference pointer so we can increment it by 1
    (*count)++;

    printf("New saying added.\n");
}

void searchSaying(char sayings[MAX_SAYINGS][MAX_LENGTH], int count)
{
    // get substring from user input
    char substring[MAX_LENGTH];
    printf("Enter a substring to search for: ");

    getchar(); // clear input buffer

    fgets(substring, MAX_LENGTH, stdin);
    substring[strcspn(substring, "\n")] = '\0'; // remove newline from substring

    printf("Sayings that contain %s: \n", substring);
    for (int i = 0; i < count; i++)
    {
        // strstr returns a pointer to the first occurence of str2 in str1, NULL if str2 isn't in str1
        // if it returns anything other than NULL, print out that string 
        if (strstr(sayings[i], substring) != NULL)
        {
            printf("%d. %s\n", i+1, sayings[i]);
        }
    }
}

void saveSayings(char sayings[MAX_SAYINGS][MAX_LENGTH], int count)
{
    // get file name from user
    char filename[31];
    printf("Enter the file name to save the sayings of: ");
    scanf("%30s", filename);

    FILE *file = fopen(filename, "w"); // open file and prepare to write to it
    // make sure we can open it
    if (file == NULL)
    {
        printf("Error opening file: %s\n", filename);
        return;
    }

    // print every saying to file stream (effectively writing it)
    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", sayings[i]);
    }

    fclose(file);
    printf("Sayings successfully saved to %s\n", filename);
}

void randomSaying(char sayings[MAX_SAYINGS][MAX_LENGTH], int count)
{
    // make sure there are actually sayings in the file
    if (count > 0)
    {
        // get random num 0 to count - 1
        int num = rand() % count;
        // print appropriate saying for random num
        printf("Random saying: \n");
        printf("%d. %s\n", num+1, sayings[num]);
    }
    // count == 0
    else
    {
        printf("Error. No sayings found in file\n");
        return;
    }
}

void every_n_saying(char sayings[MAX_SAYINGS][MAX_LENGTH], int count)
{
    // get user input
    int n;
    printf("Enter a number that you'd like to see every 'n'-th multiple of: ");
    scanf("%d", &n);

    printf("Printing every %d saying: \n", n);

    // validate input
    if (n > 0 && n <= count)
    {
        // print every multiple of n
        for (int i = n - 1; i < count; i += n)
        {
            printf("%d. %s\n", i + 1, sayings[i]);
        }
    }
    else
    {
        printf("Error. Enter a number less than the max number of sayings and greater than 0.\n");
        return;
    }
}

void is_duplicate(char sayings[MAX_SAYINGS][MAX_LENGTH], int count)
{
    int duplicate = 0; // false
    int duplicate_index; // so we can keep track of the actual duplicate

    // loop through and check everybody after 
    for (int i = 0; i < count; i++)
    {
        for (int j = i + 1; j < count; j++)
        {
            // if strcmp returns true (0), set duplicate to true (1) and keep track of where in i it happened
            if (strcmp(sayings[i], sayings[j]) == 0)
            {
                duplicate_index = i;
                duplicate = 1;
            }
        }
    }

    // if there's a duplicate, say so and print it out
    if (duplicate == 1)
    {
        printf("Duplicate saying found in file: %s\n", sayings[duplicate_index]);
    }
    else
    {
        printf("No duplicates found in file.\n");
    }
}