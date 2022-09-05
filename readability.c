#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

//Leave a "trail of breadcrumbs" for computer
int count_letters(string text);
int count_words(string text);
int count_sentences(string text);

int main(void)
{
    //Get text
    string passage = get_string("Text: ");

    //Get return values from functions + convert to float
    int letters = count_letters(passage);
    int words = count_words(passage);
    float words2 = (float) words;
    int sentences = count_sentences(passage);

    //Compute formula
    double index = (0.0588 * ((letters / words2) * 100) - 0.296 * ((sentences / words2) * 100) - 15.8);

    //Print out grade-levels
    if ((int) round(index) >= 1 && (int) round(index) < 16)
    {
        printf("Grade %i\n", (int) round(index));
    }

    else if ((int) round(index) < 1)
    {
        printf("Before Grade 1\n");
    }

    else
    {
        printf("Grade 16+\n");
    }

}

//FUNCTIONS
int count_letters(string text)
{
    int letterCount = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        //Check if letters within ASCII values 65-90, and count as letter
        if (toupper(text[i]) >= 65 && toupper(text[i]) <= 90)
        {
            letterCount = letterCount + 1;
        }
    }

    return letterCount;
}

int count_words(string text)
{
    //Number of spaces is always 1 less than total number of words, so initialize at 1
    int wordCount = 1;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 32)
        {
            wordCount = wordCount + 1;
        }
    }

    return wordCount;
}

int count_sentences(string text)
{
    int sentenceCount = 0;

    //Check for puntuation ASCII values
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == 33 || text[i] == 46 || text[i] == 63)
        {
            sentenceCount = sentenceCount + 1;
        }
    }

    return sentenceCount;
}