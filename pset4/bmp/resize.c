/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Copies a BMP, then enlargens it per user input
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ******** ERROR CHECKING AND OPENEING FILES ******** 
    
    // ensure proper usage
    if (argc != 4 || atoi(argv[1]) < 1 || atoi(argv[1]) > 100)
    {
        printf("Usage: ./resize resizing-factor infile outfile\nnote: resize-factor must be between 1 and 100");
        return 1;
    }

    // remember filenames, store n
    char* infile = argv[2];
    char* outfile = argv[3];
    int n = atoi(argv[1]);

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }
    
    
    // ******** BITMAP HEADER MGMT ********
    
    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }
    
    // create copy of infile BITMAPINFOHEADER to keep original values
    BITMAPINFOHEADER biorig;
    biorig.biSize = bi.biSize;
    biorig.biWidth = bi.biWidth;
    biorig.biHeight = bi.biHeight;
    biorig.biSizeImage = bi.biSizeImage;
    
    // modify outfile's BITMAPINFOHEADER
    bi.biWidth = bi.biWidth * n;
    bi.biHeight = bi.biHeight * n;
    
    // determine padding for old and new files' scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int paddingorig =  (4 - (biorig.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // continue BITMAPINFOHEADER modification
    bi.biSizeImage = ((padding * sizeof(char)) + (bi.biWidth * sizeof(RGBTRIPLE))) * abs(bi.biHeight);
    
    // modify outfile's BITMAPFILEHEADER
    bf.bfSize = 14 + 40 + bi.biSizeImage;
    
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    
    // ******** PIXEL MODIFICATION ********

// wrap all below in a loop that counts up to n
    // iterate over infile's scanlines | SCANLINES
    for (int i = 0, biHeight = abs(biorig.biHeight); i < biHeight; i++)
    {
        // iterate over scanline data by resize factor | RESIZE FACTOR
        for (int ii = 0; ii < n; ii++) {
            if (ii > 0) {
                // if it is not the first iteration, then we need to make a copy of the row (to repeat it n 
                // times vertically); move cursor back to beginning of row to write it again
                fseek(inptr,-1*(biorig.biWidth * sizeof(RGBTRIPLE) + (sizeof(char) * paddingorig)),SEEK_CUR);
            }
            
            // iterate over pixels in scanline | PIXELS
            for (int j = 0; j < biorig.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                for (int k = 0; k < n; k++) {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
        
            // skip over padding in inptr, if any
            fseek(inptr, paddingorig, SEEK_CUR);

            // then add it back
            for (int l = 0; l < padding; l++)
            {
                fputc(0x00, outptr);
            }
        
        } // close ii loop (loop that counts from ii to n)
    } // END SCANLINE

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks 
    return 0;
}
