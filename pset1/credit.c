#include <cs50.h>
#include <stdio.h>


int main(void)
{
    long card_number;
    int checksum = 0;
    //divider set to 10 to start at 2nd to last digit
    long divider = 10;
    int first_digit = 0;
    int second_digit = 0;
    int card_length = 0;

    // int isn't capable of holding a large enough number
    card_number = get_long_long("Number: ");

    // cardnumber % 10 returns the rightmost digit
    // dividing by multiples of 10 removes the rightmost digits
    while (divider < card_number)
    {
        int currentDigit = card_number / divider % 10 * 2;
        if (currentDigit >= 10)
        {
            // if the currentDigit * 2 is greater than 10, add it's digits separately
            checksum += currentDigit % 10;
            checksum += currentDigit / 10 % 10;
        }
        else
        {
            checksum += currentDigit;
        }
        // increase divider by 100 instead of 10 to remove 2 digits at a time
        divider *= 100;
    }

    // reset divider to 1 to target first digit
    divider = 1;

    while (divider < card_number)
    {
        int currentDigit = card_number / divider % 10;
        checksum += currentDigit;
        divider *= 100;
    }

    // check that the checksum validates correctly
    if (checksum % 10 == 0)
    {
        divider = 1;
        // find the first two digits and length of card_number to match bank
        while (divider < card_number)
        {
            first_digit = card_number / divider % 10;
            card_length += 1;
            divider *= 10;
        }
        second_digit = card_number / (divider / 100) % 10;
        if ((card_length == 13 || card_length == 16) && first_digit == 4)
        {
            printf("VISA\n");
            return 0;
        }
        else if (card_length == 16 && first_digit == 5 && (second_digit >= 1 && second_digit <= 5))
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if (card_length == 15 && first_digit == 3 && (second_digit == 4 || second_digit == 7))
        {
            printf("AMEX\n");
            return 0;
        }
    }
    // if checksum isn't valid or no bank matched, return invalid
    printf("INVALID\n");
    return 0;

}