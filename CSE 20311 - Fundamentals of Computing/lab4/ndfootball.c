/*
Will Krzastek
Fund Comp
Lab 4
Notre Dame Football Year Calculator
*/

#include <stdio.h>
#include <stdlib.h>

#define START_YEAR 1900 // global variable of starting year

// global arrays (copy-pasted from course page)
int wins[] = 
    { 6, 8, 6, 8, 5, 5, 6, 6, 8, 7, 4, 6,
    7, 7, 6, 7, 8, 6, 3, 9, 9, 10, 8, 9,
    10, 7, 9, 7, 5, 9, 10, 6, 6, 3, 6, 7, 
    6, 6, 8, 7, 7, 8, 7, 9, 8, 7, 8, 9,
    9, 10, 4, 7, 7, 9, 9, 8, 2, 7, 6, 5, 
    2, 5, 5, 2, 9, 7, 9, 8, 7, 8, 10, 8, 
    8, 11, 10, 8, 9, 11, 9, 7, 9, 5, 6, 7, 
    7, 5, 5, 8, 12, 12, 9, 10, 10, 11, 6, 9, 
    8, 7, 9, 5, 9, 5, 10, 5, 6, 9, 10, 3, 
    7, 6, 8, 8, 12, 9, 8, 10, 4, 10, 12, 11, 
    10, 11, 9, 10 };

int losses[] = 
    { 3, 1, 2, 0, 3, 4, 1, 0, 1, 0, 1, 0,
    0, 0, 2, 1, 1, 1, 1, 0, 0, 1, 1, 1,
    0, 2, 1, 1, 4, 0, 0, 2, 2, 5, 3, 1,
    2, 2, 1, 2, 2, 0, 2, 1, 2, 2, 0, 0,
    0, 0, 4, 2, 2, 0, 1, 2, 8, 3, 4, 5,
    8, 5, 5, 7, 1, 2, 0, 2, 2, 2, 1, 2,
    3, 0, 2, 3, 3, 1, 3, 4, 2, 6, 4, 5,
    5, 6, 6, 4, 0, 1, 3, 3, 1, 1, 5, 3,
    3, 6, 3, 7, 3, 6, 3, 7, 6, 3, 3, 9,
    6, 6, 5, 5, 1, 4, 5, 3, 8, 3, 1, 2,
    2, 2, 4, 3 };

#define NUM_YEARS (sizeof(wins) / sizeof(wins[0])) // how many years are in array (can change so not hardcoding)

// function prototypes
void display_record_for_year(int);
void display_years_with_min_losses(int);
void display_years_with_min_wins(int);
void display_years_with_wins_more_than_losses(int);
void display_record_for_last_5_years(int);


int main(void)
{
    // arbitrary value of choice that isn't equal to 6
    int choice = -1;

    while (choice != 6)
    {
        // print initial menu to user and get their input
        printf("\nNotre Dame Football Record Query System\n");
        printf("1. Display the record for a given year\n");
        printf("2. Display years with at least 'n' losses\n");
        printf("3. Display years with at least 'n' wins\n");
        printf("4. Display years with at least 'n' more wins than losses\n");
        printf("5. Display the record for the previous 5 years for a given year\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        // use switch statement for their choice
        switch (choice)
        {
            // call display record for year function
            case 1:
            {
                int year;
                printf("Enter the year (>= 1900): ");
                scanf("%d", &year);
                display_record_for_year(year);
                break;
            }
            // call display min loss function
            case 2:
            {
                int min_losses;
                printf("Enter the minimum number of losses: ");
                scanf("%d", &min_losses);
                display_years_with_min_losses(min_losses);
                break;
            }
            // call display min win function
            case 3:
            {
                int min_wins;
                printf("Enter the minimum number of wins: ");
                scanf("%d", &min_wins);
                display_years_with_min_wins(min_wins);
                break;
            }
            // call display difference function
            case 4:
            {
                int difference;
                printf("Enter the minimum win difference over losses: ");
                scanf("%d", &difference);
                display_years_with_wins_more_than_losses(difference);
                break;
            }
            // call display last 5 years function
            case 5:
            {
                int year;
                printf("Enter the year (>= 1905): ");
                scanf("%d", &year);
                display_record_for_last_5_years(year);
                break;
            }
            // exit program by breaking the while loop on next iteration
            case 6:
            {
                printf("Exiting program...\n");
                break;
            }
            // user didn't enter an int 1-6
            default:
                printf("Invalid choice, try again\n");
                break;
        }
    }

    return 0; // successful return code
}

void display_record_for_year(int year)
{
    // year - 1900 is the index
    int index = year - START_YEAR;

    // make sure they entered a year between 1900-current year
    if (index >= 0 && index < NUM_YEARS)
    {
        // if they entered a valid year then display the record for that year
        printf("Record for %d: Wins = %d, Losses = %d\n", year, wins[index], losses[index]);
    }
    else
    {
        printf("Invalid year entered.\n");
    }
}

void display_years_with_min_losses(int min_losses)
{
    printf("Years with at least %d losses: \n", min_losses);

    // go through loss array and check if each entry is >= min_losses
        // if so, display that year and its record
    for (int i = 0; i < NUM_YEARS; i++)
    {
        if (losses[i] >= min_losses)
        {
            printf("%d: Wins = %d, Losses = %d\n", START_YEAR + i, wins[i], losses[i]);
        }
    }
}


void display_years_with_min_wins(int min_wins)
{
    printf("Years with at least %d wins: \n", min_wins);

    // go through win array and check if each entry is >= min_wins
        // if so, display that year and its record
    for (int i = 0; i < NUM_YEARS; i++)
    {
        if (wins[i] >= min_wins)
        {
            printf("%d: Wins = %d, Losses = %d\n", START_YEAR + i, wins[i], losses[i]);
        }
    }
}


void display_years_with_wins_more_than_losses(int difference)
{
    printf("Years with at least %d more wins than losses: \n", difference);

    // go through win and loss arrays and check if the difference of each entry is >= difference
        // if so, display that year and its record
    for (int i = 0; i < NUM_YEARS; i++)
    {
        if (wins[i] - losses[i] >= difference)
        {
            printf("%d: Wins = %d, Losses = %d\n", START_YEAR + i, wins[i], losses[i]);
        }
    }
}


void display_record_for_last_5_years(int year)
{
    int index = year - START_YEAR;

    // check that year is 1905-current year
    if (index >= 5 && index < NUM_YEARS)
    {
        printf("Record for the previous 5 years: \n");
        // go 5 years back and display the year + record of each year up until the current year
        for (int i = index - 5; i < index; i++)
        {
            printf("%d: Wins = %d, Losses = %d\n", START_YEAR + i, wins[i], losses[i]);
        }
    }
    // they entered a year 1900-1904; display appropriate error message
    else if (index < 5)
    {
        printf("Entered a year between 1900-1904. 5 years have not passed.\n");
    }
    else
    {
        printf("Invalid year entered.\n");
    }
}