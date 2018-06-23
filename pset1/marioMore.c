#include <cs50.h>
#include <stdio.h>

int main(void)
{
    // declare variables
    int height;
    int spaces;
    int blocks;
    int gap;

    // ask for height until user gives a valid number
    do
    {
        height = get_int("height: ");
    }
    while (height > 23 || height < 0);

    // terminate immediately if height == 0
    if (height == 0)
    {
        return 0;
    }

    // loop from 1 to height, blocks and spaces on either side of the gap should equal height
    for (int i = 1; i <= height; i++)
    {
        for (spaces = height - 1; spaces >= i; spaces--)
        {
            printf(" ");
        }

        for (blocks = 1; blocks <= i; blocks++)
        {
            printf("#");
        }

        // 2 space gap in every line
        for (gap = 1; gap <= 2; gap++)
        {
            printf(" ");
        }

        for (blocks = 1; blocks <= i; blocks++)
        {
            printf("#");
        }

        printf("\n");
    }
}