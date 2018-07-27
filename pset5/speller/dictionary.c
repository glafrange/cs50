// Implements a dictionary's functionality

#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <stdio.h>

#include "dictionary.h"

// Defining the nodes of the linked list in the hashtable
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Declare the hash table
node *dict_ht[HT_LENGTH];

// hash function is returning the first char's place in the alphabet
int get_hash(char *word)
{
    return toupper(word[0]) - 65;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    for (int i = 0; i < HT_LENGTH; i++)
    {
        node *cursor = dict_ht[i];
        while (cursor != NULL)
        {
            if (strcasecmp(word, cursor -> word) == 0)
            {
                return true;
            }
            cursor = cursor -> next;
        }
    }
    return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    char word[LENGTH + 1];
    FILE *dict_ptr = fopen(dictionary, "r");
    if (dict_ptr == NULL)
    {
        printf("dictionary could not be opened\n");
        unload();
        return 2;
    }
    // scan each word in the dictionary until the end of file
    while (fscanf(dict_ptr, "%s", word) != EOF)
    {
        // creates new node and add it to the hash table
        node *new_node = malloc(sizeof(node));
        if (new_node == NULL)
        {
            return false;
        }
        strcpy(new_node -> word, word);
        int hash = get_hash(word);
        new_node -> next = dict_ht[hash];
        dict_ht[hash] = new_node;
    }
    fclose(dict_ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    int count = 0;
    for (int i = 0; i < HT_LENGTH; i++)
    {
        node *cursor = dict_ht[i];
        while (cursor != NULL)
        {
            count++;
            cursor = cursor -> next;
        }
    }
    return count;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < HT_LENGTH; i++)
    {
        node *cursor = dict_ht[i];
        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }
    }
    return true;
}
