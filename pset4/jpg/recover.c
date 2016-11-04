/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */
 
 #include <stdio.h>
 #include <stdlib.h>
 #include <stdint.h>
 
 typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    // open memory card file and make sure there is data within
    FILE* input = fopen("card.raw", "r");
    if (input == NULL) {
        printf("Could not read data.\n");
        return 1;
    }
    
    // make buffer to hold data in
    BYTE* block = malloc(512);
    if (block == NULL) {
        printf("You are out of memory");
        return 2;
    }
    
    // create char to hold name of image file 
    char filename[8];
    // create int to increment with every file you make - for file names
    int filecounter = 0;
    
    while (fread(block, 1, 512, input) == 512) {
    
        if (block[0] == 0xff && block[1] == 0xd8 && block[2] == 0xff && block[3] >= 0xe0 && block[3] <= 0xef ) {
            filecounter++;
        }
        
        if (filecounter > 0) {
            // when you're ready to save file
            sprintf(filename,"%03d.jpg", filecounter-1);
            FILE* img = fopen(filename,"a");
            if (img == NULL) {
                printf("Error - could not write to file %03d.jpg", filecounter-1);
                return 3;
            }
            fwrite(block, 1, 512, img);
            fclose(img);
        }
        
    }

    free(block);
    fclose(input);
    
    return 0;    
}
