// Implements a dictionary's functionality

#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of adding word
int count = 0;

// Number of buckets in hash table
const unsigned int N = 256;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    char temp[LENGTH + 1];
    int len = strlen(word);
    for(int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    temp[len] = '\0';

    int index = hash(temp);

    if (table[index] == NULL)
    {
        return false;
    }

    node* cursor = table[index];

    while (cursor != NULL)
    {
        if (strcmp(temp, cursor->word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }

    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int hash_key = 0;
    int n = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        if (isalpha(word[i]) == 0)
        {
        n = tolower(word[i]);
        hash_key += (n * hash_key) % N;
        }
    }
    size();
    return hash_key;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
    return false;
    }

    char buffer[LENGTH + 1];

    while (fscanf(file, "%s", buffer) != EOF)
    {
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            unload();
            return false;
        }
        strcpy(n->word, buffer);
        int index = hash(n->word);

        if (table[index]->next == NULL)
        {
            table[index]->next = n;
        }
        else
        {
            n->next = table[index]->next;
            table[index]->next = n;
        }
        free(n);
    }
    fclose(file);

    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    count++;
    return count;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N-1; i++)
    {
        node *cursor = table[i];
        while (cursor != NULL)
        {
                node *tmp = cursor;
                cursor = cursor->next;
                free(tmp);
        }
    }
    return true;
}
