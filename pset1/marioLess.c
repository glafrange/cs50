#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // declare variables
    int height;
    int blocks;
    int spaces;

    // keep prompting for height until the user enters a valid number
    do
    {
        height = get_int("height: ");
    }
    while (height < 0 || height > 23);

    // if user enters 0 end program
    if (height == 0)
    {
        return 0;
    }

    // loop from one to height, printed spaces and blocks add up to height
    for (int i = 1; i <= height; i++)
    {
        for (spaces = height - 1; spaces >= i; spaces--)
        {
            printf(" ");
        }
        for (blocks = 0; blocks <= i; blocks++)
        {
            printf("#");
        }
        printf("\n");
    }
}