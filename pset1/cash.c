#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // declare variables
    int change_owed;
    int coins = 0;

    // multiplying user input by 100 to get the number of cents
    // rounding the result to avoid the int being floored due to imprecision
    change_owed = round(get_float("Change owed: ") * 100);

    // while there is still change owed, subtract the largest coin possible, and increase the coins int by 1
    while (change_owed > 0)
    {
        if (change_owed >= 25)
        {
            change_owed -= 25;
            coins += 1;
        }
        else if (change_owed >= 10)
        {
            change_owed -= 10;
            coins += 1;
        }
        else if (change_owed >= 5)
        {
            change_owed -= 5;
            coins += 1;
        }
        else if (change_owed >= 1)
        {
            change_owed -= 1;
            coins += 1;
        }
    }

    printf("%i\n", coins);
}