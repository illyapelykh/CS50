/**
 * resize.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Scales a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize scale infile outfile\n");
        return 1;
    }

    // remember filenames and scale
    char* infile = argv[2];
    char* outfile = argv[3];
    int scale = atoi(argv[1]);
    if (scale < 1 || scale > 100)
    {
        printf("Input coorect scale: 1...100\n");
        return 2;
    }

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

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
        return 5;
    }

    // determine resized width and height
    int originWidth = bi.biWidth;
    int originHeight = bi.biHeight;
    bi.biWidth *= scale;
    bi.biHeight *= scale;
    
    // determine padding for scanlines
    int originPadding =  (4 - (originWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // determine resized file
    bi.biSizeImage = abs(bi.biHeight) * (bi.biWidth * sizeof(RGBTRIPLE) + padding);
    bf.bfSize = (bi.biSizeImage + 54);
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);
    
    // iterate over infile's scanlines
    for (int i = 0; i < abs(originHeight); i++)
    {
        // read each scanline scaled times
        for (int j = 0; j < scale; j++)
        {
            // iterate over pixels in scanline
            for (int k = 0; k < originWidth; k++)
            {
                // temporary storage
                RGBTRIPLE triple;

                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

                // write scaled times RGB triple to outfile
                for (int l = 0; l < scale; l++)
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                
            }
            
                // then add padding
                for (int m = 0; m < padding; m++)
                    fputc(0x00, outptr);
                
                // return to the beginning of a scanline
                if (j < scale - 1)
                    fseek(inptr, -originWidth * sizeof(RGBTRIPLE), SEEK_CUR);    
            
        }    
        // skip over padding, if any
        fseek(inptr, originPadding, SEEK_CUR);
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
