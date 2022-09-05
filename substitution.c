#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>

string cipher(string text);

int main(int argc, string argv[])
{
    //Check if user put in command line arg
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    //Initialize variables to see how many letters in the key provided, and make an array for the letters already in key
    int count = 0;
    char validate[strlen(argv[1])];

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        //Go through list of letters already in the key
        for (int j = 0; j <= i; j++)
        {
            //Repeated letter
            if (argv[1][i] == validate[j] || toupper(argv[1][i]) == toupper(validate[j]))
            {
                printf("Key must not contain repeated letters.\n");
                return 1;
            }
        }

        //Real letter
        if ((argv[1][i] >= 65 && argv[1][i] <= 90) || (argv[1][i] >= 96 && argv[1][i] <= 122))
        {
            validate[i] = argv[1][i];
            count++;
        }

        else
        {
            printf("Key must only contain alphabetic characters.\n");
            return 1;
        }

    }

    //Check for full set of letters
    if (count != 26)
    {
        printf("Key must contain 26 letters.\n");
        printf("Count: %i", count);
        return 1;
    }


    string plaintext = get_string("plaintext: ");
    string ciphertext = plaintext;

    for (int i = 0; i < strlen(plaintext); i++)
    {
        //If letter is lowercase, keep lowercase
        if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            int position = plaintext[i] - 97;
            ciphertext[i] = tolower(argv[1][position]);
        }

        //If letter is uppercase, keep uppercase
        else if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            int position = plaintext[i] - 65;
            ciphertext[i] = toupper(argv[1][position]);
        }

        //If letter is non-alphabetical, keep as whatever it was
        else
        {
            ciphertext[i] = plaintext[i];
        }
    }
    printf("ciphertext: %s\n", ciphertext);
    return 0;

}
