#include <cs50.h>
#include <stdio.h>
#define _XOPEN_SOURCE
#include <unistd.h>
#include <crypt.h>
#include <string.h>
#include <ctype.h>

// function to get the next permutation of the password
char *nextPerm(char pw[])
{
    // get the next character of the last letter
    char nextChar = pw[strlen(pw) - 1] + 1;
    // Skips the non-alphabetic characters between upper and lowercase letters
    if (nextChar >= 91 && nextChar <= 96)
    {
        nextChar = 97;
        pw[strlen(pw) - 1] = nextChar;
    }
    // Check if the nextChar is at the end of the alphabet
    else if (nextChar > 122)
    {
        // increment from last to first letter until the current letter isnt at the end of the alphabet
        for (int i = strlen(pw) - 1; i >= 0; i--)
        {
            pw[i]++;
            // increment from last to first letter
            if (pw[i] >= 122)
            {
                pw[i] = 65;
            }
            // skip non-alphabetic characters
            else if (pw[i] >= 91 && pw[i] <= 96)
            {
                pw[i] = 97;
                break;
            }
            else
            {
                break;
            }
        }
        // check if another letter needs to be added on
        bool increaseDigits = true;
        for (int i = 0; i < strlen(pw); i++)
        {
            // only add another letter if all letters arent equal to 'A'
            if (pw[i] != 65)
            {
                increaseDigits = false;
            }
        }
        // assign 'A' to the current end of string, and assign the null terminator to the index after that
        if (increaseDigits == true)
        {
            int length = strlen(pw);
            pw[length] = 'A';
            pw[length + 1] = '\0';
        }
    }
    // if nextChar isn't non-alphabetic assign it to the current end of string
    else
    {
        pw[strlen(pw) - 1] = nextChar;
    }
    return pw;
}

// main function
int main(int argc, string argv[])
{
    // if more/less than 1 command line argument exit program
    if (argc != 2)
    {
        return 1;
    }

    // declare variables
    string hash = argv[1];
    char salt[3] = { hash[0], hash[1], '\0' };
    char pw[6] = {'A', '\0'};
    string pwHash = crypt(pw, salt);

    // get the next permutation of the password guess and its hash until it matches the hash the user gave
    while (strcmp(pwHash, hash) != 0)
    {
        strcpy(pw, nextPerm(pw));
        pwHash = crypt(pw, salt);
    }

    printf("%s\n", pw);
    return 0;
}

