/*
Will Krzastek
Fund Comp
Lab 4
Primes 1-1000 Calculator
*/

#include <stdio.h>
#include <stdbool.h>

#define SIZE 1000 // we are going up to 1000

// prototype functions
void sieve(bool [], int);
void print_primes(bool [], int);

int main(void)
{
    // create initial empty array
    bool primes[SIZE];

    // fill every element with true
    for (int i = 0; i < SIZE; i++)
    {
        primes[i] = true;
    }

    // run our functions on the array
    sieve(primes, SIZE);
    print_primes(primes, SIZE);

    return 0;
}

void sieve(bool primes[], int size)
{
    // 0 and 1 are false - per the directions
    primes[0] = primes[1] = false;

    // loop from 2 to when i^2 < size isn't true (per the Sieve algorithm)
    // this works because you check all the numbers past this when you check smaller multiples of i
    for (int i = 2; i * i < size; i++)
    {
        // if this element is marked as prime then go to every multiple of it and mark it as false, because it can't be prime obviously
        if (primes[i])
        {
            for (int j = i * i; j < size; j += i)
            {
                primes[j] = false;
            }
        }
    }
    

}

void print_primes(bool primes[], int size)
{
    int count = 0;

    // loop from 2 to 1000
    for (int i = 2; i <= size; i++)
    {
        // if it's prime, then print it out with proper formatting
        if (primes[i])
        {
            printf("%4d", i);
            count++;

            // if we've printed 10 primes, print a new line
            if (count % 10 == 0)
            {
                printf("\n");
            }
        }
    }
    printf("\n"); // print new line at the end to make it look nicer
}