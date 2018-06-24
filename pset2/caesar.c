#include <stdio.h>
#include <cs50.h>
#include <string.h>

int main(int argc, string argv[])
{
    // Termiate program if there is no key passed in as an argument
    if (argc != 2)
    {
        return 1;
    }

    // Declare variables
    int key = atoi(argv[1]) % 26;
    string plaintext = get_string("plaintext: ");

    printf("ciphertext: ");

    // Loop from 0 (first index) to the length of the plaintext
    for (int i = 0; i < strlen(plaintext); i++)
    {
        // Check if the character at this index is an Uppercase letter
        if (plaintext[i] >= 65 && plaintext[i] <= 90)
        {
            // check if this character will go past Z when the key is added to it
            if (plaintext[i] + key > 90)
            {
                // add the absolute difference between the current character and Z to the character before A
                printf("%c", 64 + abs(plaintext[i] + key - 90));
            }
            else
            {
                // else add the key to the plaintext and print
                printf("%c", plaintext[i] + key);
            }
        }
        // Check if the character at this index is an Lowercase letter
        else if (plaintext[i] >= 97 && plaintext[i] <= 122)
        {
            // check if this character will go past z when the key is added to it
            if (plaintext[i] + key > 122)
            {
                // add the absolute difference between the current character and z to the character before a
                printf("%c", 96 + abs(plaintext[i] + key - 122));
            }
            else
            {
                // else add the key to the plaintext and print
                printf("%c", plaintext[i] + key);
            }
        }
        // If the character is not a letter than print without changing it
        else
        {
            printf("%c", plaintext[i]);
        }
    }

    printf("\n");

    return 0;
}