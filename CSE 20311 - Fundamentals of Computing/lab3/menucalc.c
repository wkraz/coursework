/*
Will Krzastek
Fund Comp
Lab 3
Calculator from Text Input
*/

#include <stdio.h>
#include <math.h>

// function prototypes
int get_operation(void);
double get_number1(void);
double get_number2(void);
double add(double n1, double n2);
double subtract(double n1, double n2);
double multiply(double n1, double n2);
double divide(double n1, double n2);
double computation(int operation, double num1, double num2);

int main(void)
{
    while (1) // while True loop
    {
        // use user-defined function
        int operation = get_operation();

        // if they choose to exit, break the while true loop
        if (operation == 5)
        {
            printf("Understood. Exiting...\n");
            break;
        }
        
        // get the two doubles
        double num1 = get_number1();
        double num2 = get_number2();

        // do the computation the user input
        double result = computation(operation, num1, num2);

        // addition
        if (operation == 1)
        {
            printf("(%.2lf) + (%.2lf) = %.2lf\n", num1, num2, result);
        }
        // subtraction
        else if (operation == 2)
        {
            printf("(%.2lf) - (%.2lf) = %.2lf\n", num1, num2, result);
        }
        // multiplication
        else if (operation == 3)
        {
            printf("(%.2lf) * (%.2lf) = %.2lf\n", num1, num2, result);
        }
        // division
        else if (operation == 4)
        {
            // make sure we don't divide by 0
            if (num2 == 0)
            {
                printf("Error. Cannot divide by 0\n");
            }
            else
            {
                printf("(%.2lf) / (%.2lf) = %.2lf\n", num1, num2, result);
            }
        }
        // check for invalid input
        else
        {
            printf("Error. Must choose an integer 1-4\n");
        }
        printf("\n"); // new line at the end to separate each block
    }

    return 0; // successful return
}

int get_operation(void)
{
    int n;
    printf("What would you like to do?\n");
    printf("Enter 1 for addition\n2 for subtraction\n3 for multiplication\n4 for division\n5 to exit\n");
    printf("Enter your choice: ");
    scanf("%d", &n);
    return n;
}

double get_number1(void)
{
    double num1;
    printf("Enter the first number: ");
    scanf("%lf", &num1);
    return num1;
}

double get_number2(void)
{
    double num2;
    printf("Enter the second number: ");
    scanf("%lf", &num2);
    return num2;
}

double add(double n1, double n2)
{
    return (n1 + n2);
}

double subtract(double n1, double n2)
{
    return (n1 - n2);
}

double multiply(double n1, double n2)
{
    return (n1 * n2);
}

double divide(double n1, double n2)
{
    return (n1 / n2);
}

double computation(int operation, double num1, double num2)
{
    // use the user defined functions to compute what the user input
    if (operation == 1)
    {
        return add(num1, num2);
    }
    else if (operation == 2)
    {
        return subtract(num1, num2);
    }
    else if (operation == 3)
    {
        return multiply(num1, num2);
    }
    else if (operation == 4)
    {
        return divide(num1, num2);
    }
    // user input something other than 1-4
    else
    {
        printf("Error, invalid operation choice\n");
        return 0; // we don't want this to happen
    }
}