#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int encodeUpper(char x, int indx);
int encodeLower(char x, int indx);

int main(int argc, string argv[])
{
    if (argc != 2 || atoi(argv[1]) < 1) {
        printf("Invalid input. Please supply one integer to serve as encryption key\n");
        return 1;
    }
    
    int index = atoi(argv[1]);
    string text = GetString();
    
    for (int i = 0, s = strlen(text); i < s; i++) {
        if (isupper(text[i])) {
            //printf("%c  ", text[i]);
            printf("%c", encodeUpper(text[i], index));
        }
        else if (islower(text[i])) {
            //printf("%c  ", text[i]);
            printf("%c", encodeLower(text[i], index));
        }
        else {
            printf("%c", text[i]);
        }
    }
    
    printf("\n");
    return 0;
    
}

int encodeUpper(char x, int indx) {
    x = (x - 65 + indx) % 26;
    return x + 65;
}

int encodeLower(char x, int indx) {
    x = (x - 97 + indx) % 26;
    return x + 97;
}

