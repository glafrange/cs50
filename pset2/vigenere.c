#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        return 1;
    }

    int key[strlen(argv[1])];
    string plaintext;
    // index for looping through the key
    int count = 0;

    // loop through the command line argument and turn the string into keys
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        // if there are any non-alphanumeric characters in the string exit the program
        if (isalpha(argv[1][i]) == false)
        {
            return 1;
        }
        if (argv[1][i] >= 65 && argv[1][i] <= 90)
        {
            key[i] = argv[1][i] - 65;
        }
        else if (argv[1][i] >= 97 && argv[1][i] <= 122)
        {
            key[i] = argv[1][i] - 97;
        }
    }

    // Get string
    plaintext = get_string("plaintext: ");
    printf("ciphertext: ");

    for (int i = 0; i < strlen(plaintext); i++)
    {
        bool alpha = false;
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            // check if this character will go past Z when the key is added to it
            if (plaintext[i] + key[count] > 90)
            {
                // add the absolute difference between the current character and Z to the character before A
                plaintext[i] = 64 + abs(plaintext[i] + key[count] - 90);
            }
            else
            {
                // else add the key to the plaintext and print
                plaintext[i] = plaintext[i] + key[count];
            }
            alpha = true;
        }
        // Check if the character at this index is an Lowercase letter
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            // check if this character will go past z when the key is added to it
            if (plaintext[i] + key[count] > 122)
            {
                // add the absolute difference between the current character and z to the character before a
                plaintext[i] = 96 + abs(plaintext[i] + key[count] - 122);
            }
            else
            {
                // else add the key to the plaintext and print
                plaintext[i] = plaintext[i] + key[count];
            }
            alpha = true;
        }
        // if the current character is alphanumeric increment the count;
        if (alpha == true)
        {
            count++;
        }
        if (count == strlen(argv[1]))
        {
            count = 0;
        }
    }
    printf("%s\n", plaintext);
    return 0;
}