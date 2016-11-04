#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    printf("Please enter amount of change owed: ");
    float total = GetFloat();
    
    // Validate input
    while (total < 0) {
        printf("Seems like you didn't get paid enough! Please enter a positive number: ");
        total = GetFloat();
    }
    
    // Keep track of the amount of coins; change total to int and round (to avoid precision errors)
    int amt_coins = 0;
    total = round(total * 100);
    
    // On with the fun...use while loops to keep subtracting and checking if total is greater than unit of change
    // if not, move on to next unit
    while (total >= 25) {
        total -= 25;
        amt_coins++;
    }
    while (total >= 10) {
        total -= 10;
        amt_coins++;
    }
    while (total >= 5) {
        total -= 5;
        amt_coins++;
    }
    while (total >= 1) {
        total -= 1;
        amt_coins++;
    }
    
    printf("%i\n",amt_coins);
}