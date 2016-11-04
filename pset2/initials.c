#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    //printf("Please enter your name: ");
    string name = GetString();
    int space = 0;
    
    // Get number of initials (by way of calculating number of spaces)
    for (int i = 0, s = strlen(name); i < s; i++) {
        if (name[i] == ' ') {
            space++;
        }
    }
    
    // Declare array of correct size to hold initials and stick first letter in there
    char initials[space+1];
    initials[0] = name[0];
    int ctrl = 1;
    
    // Loop through string, finding all spaces and putting following letter in array
    for (int i = 0, s = strlen(name); i < s; i++) {
        if (name[i] == ' ') {
            initials[ctrl] = name[i+1];
            ctrl++;
        }
    }
    
    // Loop through initials array, make uppercase and print
    for (int i = 0; i < (space+1); i++) {
        initials[i] = toupper(initials[i]);
        printf("%c",initials[i]);
    }
    printf("\n");
    
}