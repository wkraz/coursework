#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_STATES 100

// state struct with - abbreviation, capital, name, year joined the union (in order of csv)
typedef struct {
    char abv[4];
    char capital[100];
    char name[100];
    int year;
} State;

// prototypes
int load_states(FILE *, State []);
void print_menu(void);
void to_lower(char *);
void list_all_states(State [], int);
void list_capital_by_name(State [], int);
void list_info_by_abv(State [], int);
void list_states_by_year(State [], int);

int main()
{
    // initialize struct array
    State states[MAX_STATES];

    // get file name from user
    char filename[100];
    printf("Enter a file name: ");
    scanf("%s", filename);

    // open file and make sure it exists
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error opening the file: %s\n", filename);
        return 1;
    }

    // call user defined function to see # states and load them from file --> array
    int count = load_states(file, states);
    fclose(file); // done with file now so close it

    int choice = -1; // arbitrary choice that won't conflict w/ condition: != 5
    while (choice != 5)
    {
        // print menu and get user input
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // clear input buffer (for fgets call in function 2)

        // call appropriate function depending on user input
        switch (choice)
        {
            case 1:
                list_all_states(states, count);
                break;
            case 2:
                list_capital_by_name(states, count);
                break;
            case 3:
                list_info_by_abv(states, count);
                break;
            case 4:
                list_states_by_year(states, count);
                break;
            case 5:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again\n");
                break;
        }
    }


    return 0;
}

int load_states(FILE *file, State states[])
{
    char line[256];
    int count = 0;

    // read each line with fgets
    while (fgets(line, sizeof(line), file))
    {
        // tokenize the line with strtok
        // this will return [ABV]\0...
        char *token = strtok(line, ",");
        strcpy(states[count].abv, token);

        // this will start at \0 and read until next comma
        token = strtok(NULL, ",");
        strcpy(states[count].name, token);

        // same as above
        token = strtok(NULL, ",");
        strcpy(states[count].capital, token);

        // this will read from last \0 and read until end
        token = strtok(NULL, ",");
        states[count].year = atoi(token); // read as string, convert to int

        count++;
    }

    return count; // length of states arr
}

void to_lower(char *str)
{
    int i = 0;
    // convert each letter in string to lowercase
    while (str[i] != '\0')
    {
        str[i] = tolower(str[i]);
        i++;
    }
}

void list_all_states(State states[], int count)
{
    // title
    printf("\nList of all states:\n");
    printf("Abbreviation | Name            | Capital         | Year Joined\n");
    printf("---------------------------------------------------------------\n");
    // print each state's info w/ appropriate formatting
    for (int i = 0; i < count; i++)
    {
        printf("%-13s %-16s %-16s %d\n", states[i].abv, states[i].name, states[i].capital, states[i].year);
    }
}

void list_capital_by_name(State states[], int count)
{
    // get state's name from user
    char name[100];
    printf("Enter the state's name: ");
    fgets(name, sizeof(name), stdin);

    // clean name (remove \n and convert it all to lowercase)
    if (name[strlen(name) - 1] == '\n')
        name[strlen(name) - 1] = '\0';
    to_lower(name);

    // look at each name in states array and compare it to what the user input
    for (int i = 0; i < count; i++)
    {
        char temp[100];
        strcpy(temp, states[i].name);
        to_lower(temp);
        // if they match, print the name and capital and return (exit the function)
        if (strcmp(temp, name) == 0)
        {
            printf("The capital of %s is %s\n", states[i].name, states[i].capital);
            return;
        }
    }

    // if we reach here that means we didn't find a match, so print an error message 
    printf("Error. Cannot find a state with the name %s in the data file\n", name);
}

void list_info_by_abv(State states[], int count)
{
    // get abbreviation from user
    char abv[4];
    printf("Enter the state's abbreviation: ");
    scanf("%s", abv);
    to_lower(abv);

    // same thing as function above, compare every abbreviation to user input and display/return if they match
    for (int i = 0; i < count; i++)
    {
        char temp[4];
        strcpy(temp, states[i].abv);
        to_lower(temp);
        if (strcmp(temp, abv) == 0)
        {
            printf("State: %s, Capital: %s, Year Joined: %d\n", states[i].name, states[i].capital, states[i].year);
            return;
        }
    }

    // error if we get here
    printf("Error. Cannot find a state with the abbreviation %s in the data file\n", abv);
}

void list_states_by_year(State states[], int count)
{
    // get year from user
    int year;
    printf("Enter the year: ");
    scanf("%d", &year);

    printf("States that joined the union on or before %d:\n", year);
    // check each state's year and print it if it's leq the user input year
    for (int i = 0; i < count; i++)
    {
        if (states[i].year <= year)
        {
            printf("%s joined in %d\n", states[i].name, states[i].year);
        }
    }
}

void print_menu(void)
{
    // print menu of choices for user
    printf("\nMenu Options:\n");
    printf("1. List all states\n");
    printf("2. List a state's capital by name\n");
    printf("3. List a state's info by abbreviation\n");
    printf("4. List all states by the year they joined the union\n");
    printf("5. Exit\n");
}