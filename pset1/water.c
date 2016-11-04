// Shower spits out 1.5 gallons water/min
// 1 gallon = 128oz, 1 bottle = 16oz

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Please enter the length of your daily shower (in minutes): ");
    int showerTime = GetInt();
    while (showerTime < 0) { 
        printf("Please enter a positive number: ");
        showerTime = GetInt();
    }
    int btlWater = (showerTime * 1.5 * 128)/16;
    printf("minutes: %i\n", showerTime);
    printf("bottles: %i\n", btlWater);
    
}