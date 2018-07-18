#include <cs50.h>
#include <stdio.h>
#include "bmp.h"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        return 1;
    }

    char *infile = argv[1];
    char *outfile = argv[2];

    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    bi.biHeight *= reps;
    bi.biWidth *= reps;
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;

    // looping through lines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        // looping through pixels in a line
        for (int j = 0, biWidth = bi.biWidth; j < biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // turn white pixels black
            if (triple.rgbtRed == 0xff && triple.rgbtBlue == 0xff && triple.rgbtGreen == 0xff)
            {
                triple.rgbtRed = 0x00;
                triple.rgbtGreen = 0x00;
                triple.rgbtBlue = 0x00;
            }
            // turn other pixels white
            else
            {
                triple.rgbtRed = 0xff;
                triple.rgbtBlue = 0xff;
                triple.rgbtGreen = 0xff;
            }

            // write rgb triple to output
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
        }

        // skip padding
        fseek(inptr, padding, SEEK_CUR);

        // add padding
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    return 0;
}