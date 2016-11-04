// First get pyramid height from user, must be positive and <= 23

#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("Please enter the height of your half-pyramid: ");
    int height = GetInt();
    
    // Keep asking until user gives correct input
    while (height < 0 || height > 23) {
        if (height < 0) printf("Height must be positive. Please re-enter: ");
        else printf("The maximum height is 23. Please re-enter: ");
        height = GetInt();
    }
    
    // Outer loop controls rows
    for (int i = 0; i < height; i++) {
        // Inner loop controls columns
        for (int j = 0; j <= height; j++) {
            // initiate control var; determines when spaces stop and #'s begin being printed
            int ctrl = (height - 1) - i;
            if (j >= ctrl) {
                printf("#");
            }
            else {
                printf(" ");
            }
        }
        printf("\n");
    }
    
}