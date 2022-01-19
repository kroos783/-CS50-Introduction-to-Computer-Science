#include <strings.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// type def node
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// N = number of buckets
const unsigned int N = 26;
int dict_size = 0;

node *table[N];

bool check(const char *word)
{
    char temp[LENGTH + 1];
    int len = strlen(word);
    for (int i = 0; i < len; i++)
    {
        temp[i] = tolower(word[i]);
    }
    temp[len] = '\0';

    int index = hash(temp);

    if (table[index] == NULL)
    {
        return false;
    }

    node *cursor = table[index];

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

unsigned int hash(const char *word)
{
    // TODO
    return tolower(word[0]) - 'a'; // turn lower letter by letter
}

bool load(const char *dictionary)
{
    // TODO
    FILE *file = fopen(dictionary, "r"); // load dictionary
    if (file == NULL)
    {
        return false;
    }

    char word[LENGTH + 1];

    while (fscanf(file, "%s\n", word) != EOF) // scan file word by word + run hash function and copy value in bucket
    {
        dict_size++;

        node *newWord = malloc(sizeof(node));

        strcpy(newWord->word, word);

        int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = newWord;
            newWord->next = NULL;
        }

        else
        {
            newWord->next = table[index];
            table[index] = newWord;
        }

    }

    fclose(file);


    return true;
}

unsigned int size(void)
{
    // TODO
    return dict_size;
}

bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++) // list 26 buckets for unload
    {
        if (table[i] != NULL)
        {
            node *cursor = NULL;

            while (table[i] != NULL)
            {
                cursor = table[i];
                table[i] = cursor->next;
                free(cursor);
            }
        }
    }

    return true;
}
