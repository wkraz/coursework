/*
Will Krzastek
Fund Comp
Lab 4
Grade Average & Standard Deviation Calculation
*/

#include <stdio.h>
#include <math.h>

// function prototypes
float get_average(int [], int);
float get_stdev(int [], int, float);

int main(void)
{
    // grades array (copy/pasted from course website)
    int grades[] =
    { 96,73,62,87,80,63,93,79,71,99,
        82,83,80,97,89,82,93,92,95,89,
        71,97,91,95,63,81,76,98,64,86,
        74,79,98,82,77,68,87,70,75,97,
        71,94,68,87,79 };

    // get length of grades[] and display to user
    int num_grades = sizeof(grades) / sizeof(grades[0]);
    printf("There are %d grades\n", num_grades);

    // compute average and standard deviation
    float average = get_average(grades, num_grades);
    float stdev = get_stdev(grades, num_grades, average);

    // display results to user
    printf("Average: %.2lf\n", average);
    printf("Standard deviation: %.2lf\n", stdev);


    return 0;
}

// function definitions
float get_average(int grades[], int num_grades)
{
    int sum = 0;
    for (int i = 0; i < num_grades; i++)
    {
        sum += grades[i];
    }
    
    return (float) sum / num_grades;
}

float get_stdev(int grades[], int num_grades, float average)
{
    float variance = 0;
    for (int i = 0; i < num_grades; i++)
    {
        variance += pow(grades[i] - average, 2);
    }
    variance /= num_grades;

    return sqrt(variance);
}