// Implements a dictionary's functionality
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int countWord = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashcode = hash(word);
    // Create cursor variable
    node *cursor = table[hashcode];
    // Loop until the end of the linked list
    while (cursor != NULL)
    {
        // Check if the words are the same
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        // Otherwise, move cursor to the next node
        cursor = cursor->next;
    }
    // Otherwise, move cursor to the next node
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int value = 0;
    int i;

    for (i = 0; word[i] != '\0'; i++)
    {
        value += tolower(word[i]);
    }
    return value % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE *DictFile = fopen(dictionary, "r");

    // Check if return value is NULL
    if (DictFile == NULL)
    {
        return false;
    }

    // Read string from file
    char str[LENGTH + 1];
    while (fscanf(DictFile, "%s", str) != EOF)
    {
        node *temp = malloc(sizeof(node));
        if (temp == NULL)
        {
            return false;
        }
        strcpy(temp->word, str);

        // Use the hash function
        int hashcode = hash(str);

        if (table[hashcode] == NULL)
        {
            // Point temp to NULL
            temp->next = NULL;
        }
        else
        {
            // Point temp to the first node of linked list
            temp->next = table[hashcode];
        }
        // Point the header to temp
        table[hashcode] =  temp;

        countWord += 1;
    }
    // Close the file
    fclose(DictFile);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return countWord;
}

bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *temp = cursor;
            cursor = cursor->next;
            free(temp);
        }

        table[i] = NULL;
    }

    return true;
}
