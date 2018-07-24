#include <cs50.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    // Check for correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover image");
        return 1;
    }

    char *infile = argv[1];

    // Open raw file to read
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    bool eof = true;
    int jpgCount = 0;
    char fileName[8];
    FILE *img = NULL;
    int bufferLength = 512;

    while (eof)
    {
        unsigned char buffer[bufferLength];
        bufferLength = fread(buffer, 1, 512, inptr);
        // check if end of file has been reached
        if (bufferLength != 512)
        {
            eof = false;
        }
        // check if new jpg has been found
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            // close last file before opening new one
            if (img != NULL)
            {
                fclose(img);
            }
            sprintf(fileName, "%03i.jpg", jpgCount);
            jpgCount++;
            img = fopen(fileName, "w");
            fwrite(buffer, bufferLength, 1, img);
        }
        // write jpg
        else if (img != NULL)
        {
            fwrite(buffer, bufferLength, 1, img);
        }
    }

    fclose(inptr);
}