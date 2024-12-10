/*
Will Krzastek
Fund Comp
Lab 2
Mortgage calculator 
*/

#include <stdio.h>

int main()
{
    // Initialize everything
    double initial, interest_rate, interest, monthly_payment, balance, payment;
    double total = 0;
    int month = 0;

    // Get user input
    printf("Enter the initial amount, interest rate, and monthly payment: ");
    scanf("%lf %lf %lf", &initial, &interest_rate, &monthly_payment);

    // input validation: can't be negative rate
    // keep prompting until they input a non-negative rate
    while (interest_rate < 0)
    {
        printf("Invalid input. Interest rate must be positive. Try again: ");
        scanf("%lf", &interest_rate);
    }

    // Title row -- formatted
    printf("%-8s %-5s %-5s %s\n", "Month", "Payment", "Interest", "Balance");

    balance = initial; // nothing has happened yet
    interest_rate /= 100; // percent --> decimal
    interest = (interest_rate / 12) * balance; // see our initial interest payment -- this is the biggest one so just check this

    // if the monthly payment is less than the interest, exit with return code 1
    if (monthly_payment < interest)
    {
        printf("Error. Monthly payment is too small and balance has increased. Exiting with code 1.\n");
        return 1;
    }

    // while we have a positive balance, run the loop
    while (balance > 0)
    {
        month++;
        interest = (interest_rate / 12) * balance; // interest rate is annual so divide by 12 and multiply by balance to see how much was lost
        payment = monthly_payment - interest; // how much money is lost a month

        balance -= payment; // update balance 

        // if we have a negative balance, we're at the end
        if (balance < 0)
        {
            monthly_payment += balance; // balance is negative, so add it to the monthly payment to see how much we actually paid to get to 0
            balance = 0.00; // set balance to 0 now
        }

        total += monthly_payment; // update total amount paid 

        // display a row of the table -- formatted
        printf("%-8d $%-5.2f $%-5.2f $%.2f\n", month, monthly_payment, interest, balance);
    }

    // get the number of years and months (remainder) from what we calculated above
    int year = month / 12;
    int new_months = month % 12;

    // Display results to user
    printf("You paid a total of $%.2lf over %d years and %d months.\n", total, year, new_months);

    return 0;
}