/*
Will Krzastek
Fund Comp
Lab 1
Football Score Formula
*/

#include <stdio.h>

int main(void)
{
    // initialize variables
    int numTD, numEP, numFG, numS, points;

    // get user inputs
    printf("Enter the number of touchdowns: ");
    scanf("%d", &numTD);

    printf("Enter the number of extra points: ");
    scanf("%d", &numEP);

    printf("Enter the number of field goals: ");
    scanf("%d", &numFG);

    printf("Enter the number of safeties: ");
    scanf("%d", &numS);

    // calculating total points
    points = numTD * 6 + numEP + numS * 2 + numFG * 3;
    printf("The total points scored by the Fighting Irish: %d\n", points);

}