#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


int main(int argc, char *argv[])
{
    typedef uint8_t BYTE;
    const int BLOCK_SIZE = 512;


    FILE *f = fopen(argv[1], "r");
    //Make sure to accept 2 command line args and valid file
    if (argc != 2 || f == NULL)
    {
        printf("Usage: ./recover filename\n");
        return 1;
    }

    BYTE buffer[BLOCK_SIZE];


    int jpgCount = 0;
    char *filename = malloc(9 * sizeof(char));
    FILE *jpg = NULL;

    while (fread(&buffer, BLOCK_SIZE, 1, f) == 1)
    {
        //BLOCK CONTAINS HEADER FILE CODING FOR JPG...
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {

            if (jpgCount == 0)
            {
                //CREATE NEW JPG FILE TO WRITE TO
                sprintf(filename, "%03i.jpg", jpgCount);
                jpg = fopen(filename, "w");

                //WRITE THE JPG BLOCK TO THE NEW JPG FILE
                fwrite(&buffer, BLOCK_SIZE, 1, jpg);

                jpgCount++;
            }

            else
            {
                fclose(jpg);
                //CREATE NEW JPG FILE TO WRITE TO
                sprintf(filename, "%03i.jpg", jpgCount);
                jpg = fopen(filename, "w");

                //WRITE THE JPG BLOCK TO THE NEW JPG FILE
                fwrite(&buffer, BLOCK_SIZE, 1, jpg);
                jpgCount++;
            }

        }

        //Continuation of JPG
        else if (jpgCount >= 1)
        {
            fwrite(&buffer, BLOCK_SIZE, 1, jpg);
        }

    }

    fclose(f);
    fclose(jpg);
    free(filename);

    return 0;


}
