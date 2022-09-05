#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1 || height > 8);

    for (int i = 0; i < height; i++) //creates each row
    {
        //We want x spaces, where x is height - 1, height - 2, ...
        // we want y hashes, where y is 1, 2, up to height

        //spaces
        for (int j = height - 1; j > i; j--)
        {
            printf(" ");
        }

        //hashes right centered
        for (int h = 0; h <= i; h++)
        {
            printf("#");
        }

        printf("  ");

        //hashes left centered
        for (int h = 0; h <= i; h++)
        {
            printf("#");
        }

        printf("\n");
    }
}