#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int encodeUpper(char x, char indx, int indx_len);
int encodeLower(char x, char indx, int indx_len);

int main(int argc, string argv[])
{
    if (argc != 2) {
        printf("Invalid input. Please supply one word to serve as encryption key\n");
        return 1;
    }
    for (int i = 0, j = strlen(argv[1]); i < j; i++) {
        if (!isalpha(argv[1][i])) {
            printf("Invalid input. Please supply a word to serve as encryption key\n");
            return 1;
        }
    }
    
    // Store string that will be used as key, store length of key, and make j to increment key
    string index = argv[1];
    int index_len = strlen(index);
    int j = 0;
    
    // Store text to be converted
    string text = GetString();
    
    for (int i = 0, s = strlen(text); i < s; i++) {
        // If the character is upper case
        if (isupper(text[i])) {
            // Call appropriate function, then increment j
            printf("%c", encodeUpper(text[i], index[j%index_len], index_len));
            j++;
        }
        // If the character is lower case
        else if (islower(text[i])) {
            // Call appropriate function, then increment j
            printf("%c", encodeLower(text[i], index[j%index_len], index_len));
            j++;
        }
        else {
            // If the character is not a letter, do nothing and don't increment key
            printf("%c", text[i]);
        }
    }
    
    printf("\n");
    return 0;
    
}

int encodeUpper(char x, char indx, int indx_len) {
    // Get key to alpha value by doing appropriate math based on upper or lower case
    if (isupper(indx)) indx = indx - 65;
    else indx = indx - 97;
    // Get character we're working on into alpha value, then increase by key
    x = (x - 65 + indx) % 26;
    return x + 65;
}

int encodeLower(char x, char indx, int indx_len) {
    // Get key to numeric value by doing appropriate math based on upper or lower case
    if (isupper(indx)) indx = indx - 65;
    else indx = indx - 97;
    // Get character we're working on into alpha value, then increase by key
    x = (x - 97 + indx) % 26;
    return x + 97;
}

