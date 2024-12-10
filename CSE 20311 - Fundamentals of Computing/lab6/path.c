/*
Will Krzastek
Lab 6
Program that calculates path distance
*/

#include <stdio.h>
#include <math.h>

typedef struct {
    float x;
    float y;
} Point;

int read_values(FILE *, Point []);
float find_distance(Point, Point);
void display(Point);

int main()
{
    // get file name from user
    char filename[100];
    printf("Enter a file name: ");
    scanf("%s", filename);

    // open file and make sure it exists
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Error, could not open file: %s\n", filename);
        return 1;
    }

    // make points array
    Point points[30];

    // use read_values function to get length of array and read it, then close file
    int count = read_values(file, points);
    fclose(file);

    // print first 2 lines of table
    printf("There are %d points:\n\n", count);
    printf("  x   |   y\n------+--------\n");

    // calculate distance between all points and display the point
    float distance = 0;
    for (int i = 0; i < count - 1; i++)
    {
        distance += find_distance(points[i], points[i + 1]);
        display(points[i]);
    }
    display(points[count - 1]); // display last point

    printf("\nThe length of the path through them is %.2f\n", distance);

    
    return 0;
}

int read_values(FILE *file, Point arr[])
{
    int i = 0; // counter

    // read x and y into the Point arr until a valid x and y don't exist
    while (fscanf(file, "%f %f", &arr[i].x, &arr[i].y) == 2)
    {
        i++;
    }

    return i; // return the counter to show the length of the array
}

float find_distance(Point p, Point q)
{
    return sqrt(pow((p.x - q.x), 2) + pow((p.y - q.y), 2));
}

void display(Point p)
{
    printf("%5.1f | %6.1f \n", p.x, p.y);
}