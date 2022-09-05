#include <cs50.h>
#include <stdio.h>

int main(void)
{
    //Initialize variables
    int counter = 1;
    long cardNum = get_long("Number: ");
    int split;
    int sum1 = 0;
    int sum2 = 0;
    long first2;

    //Iterate through card numbers to find length
    for (int i = 1; i <= 16; i++)
    {
        //single digit (last)
        int rem = cardNum % 10;

        if (i % 2 == 0)
        {
            //Get every other digit starting from second to last
            if (rem * 2 >= 10)
            {
                split = ((rem * 2) % 10) + 1;
                sum1 = sum1 + split;
            }

            else
            {
                sum1 = sum1 + (rem * 2);

            }
        }

        //Get sum of leftover digits
        else if (i % 2 == 1)
        {
            sum2 = sum2 + rem;
        }

        //If only one digit left, break out of loop
        if (cardNum < 10)
        {
            counter = i;
            break;
        }

        //Get first two digits
        else if (cardNum / 100 < 1)
        {
            first2 = cardNum;
        }

        //Decrease card number length by one each time
        cardNum = (cardNum - rem) / 10;

    }


    //Add sums
    int total = sum1 + sum2;

    //Requirements: AMEX 15, 34 or 37; MASTER 16, 51-55; VISA 13/16, 4

    if (total % 10 == 0 && counter == 15)
    {
        if (first2 == 34 || first2 == 37)
        {
            printf("AMEX\n");
        }

        else
        {
            printf("INVALID\n");
        }

    }

    else if (first2 == 51 || first2 == 52 || first2 == 53 || first2 == 54 || first2 == 55)
    {
        if (total % 10 == 0 && counter == 16)
        {
            printf("MASTERCARD\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else if (total % 10 == 0 && counter == 13)
    {
        if (first2 - 40 >= 0 && first2 - 40 <= 9)
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else if (total % 10 == 0 && counter == 16)
    {
        if (first2 - 40 >= 0 && first2 - 40 <= 9)
        {
            printf("VISA\n");
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }

}