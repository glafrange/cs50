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
int HT_SIZE = 0;

node *dict_ptrs[143091];
int dict_ptrs_index = 0;

// hash function is returning the first char's place in the alphabet
int get_hash(const char *word)
{
    unsigned int hash = 0;
    for (int i = 0; i < strlen(word); ++i)
    {
        hash = 31 * hash + toupper(word[i]);
    }
    return hash % HT_LENGTH;
}

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *cursor = dict_ht[get_hash(word)];
    while (cursor != NULL)
    {
        if (strcasecmp(word, cursor -> word) == 0)
        {
            return true;
        }
        cursor = cursor -> next;
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
        dict_ptrs[dict_ptrs_index++] = new_node;
        HT_SIZE++;
    }
    fclose(dict_ptr);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return HT_SIZE;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < dict_ptrs_index; i++)
    {
        free(dict_ptrs[i]);
    }
    return true;
}
