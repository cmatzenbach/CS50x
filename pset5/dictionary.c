/**
 * dictionary.c
 *
 * Computer Science 50
 * Problem Set 5
 *
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <string.h>

#include "dictionary.h"

#define HASHTABLE_SIZE 17011

// counting variables to be used
int loaded_words = 0;
int misspelled_words = 0;

// declare struct for hash table nodes
typedef struct _node {
    char word[LENGTH+1];
    struct _node* next;
} node;

// declare hash table for dictionary
node* hashtable[HASHTABLE_SIZE];


/**
 * Hash functions
 */

// credit to u/delipity in r/cs50 (https://www.reddit.com/r/cs50/comments/1x6vc8/pset6_trie_vs_hashtable/)
int hashIt(const char* key) {
    unsigned int hash = 0;
    for (int i=0, n=strlen(key); i<n; i++)
        hash = (hash << 2) ^ key[i];
    return hash % HASHTABLE_SIZE;
}

// credit to dasblinkenlight on stackoverflow (http://stackoverflow.com/questions/20462826/hash-function-for-strings-in-c)
int hashtwo (const char* word)
{
    unsigned int hash = 0;
    for (int i = 0 ; word[i] != '\0' ; i++)
    {
        hash = 31*hash + word[i];
    }
    return hash % HASHTABLE_SIZE;
}


/**
 * Helper functions
 */
 
 // actually wrote it myself!  hashsearch function for searching strings
bool hashSearch (node* head, const char* search) {
    node* ptr = head;
    
    while (ptr != NULL) {
        int total = 0;
        for (int i = 0, n = strlen(search); i < n; i++) {
            if (ptr->word[i] == search[i]) total++;
        }
        if (total == strlen(ptr->word)) {
            return true;
        }
        else {
            ptr = ptr->next;
        }
    }
    return false;
}

// String Lower function - credit to Noir at http://cboard.cprogramming.com/
// http://cboard.cprogramming.com/c-programming/88987-strcmp-problem-capital-letters.html
char* strLower(char* str) {
  char *temp;
 
  for (temp = str; *temp; temp++) {
    *temp = tolower(*temp);
  }
 
  return str;
}

// Free Hashtable function - credit to Alastair Poole for the function - modified to fit program
// http://web.textfiles.com/hacking/DYNAMICHELL/hashtables.txt
void hashtable_free(void)
{
    node *tmp;
	node *fwd;

	for(int i = 0; i < HASHTABLE_SIZE; i++) {
	    tmp = hashtable[i];
	    while(tmp != NULL) {
	        fwd = tmp->next;
		    free(tmp);
		    tmp = fwd;
	    }
	}
}



/**
 * SPELLER FUNCTIONS START
 * 
 * Returns true if word is in dictionary else false.
 */
bool check(const char* word)
{
    char* lowercase;
    lowercase = malloc(strlen(word) + 1);
    strcpy(lowercase,word);
    lowercase = strLower(lowercase);
    
    int srch = hashtwo(lowercase);

    if (hashSearch(hashtable[srch], lowercase)) {
        free(lowercase);
        return true;
    }
    else {
        int *words = &misspelled_words;
        *words += 1;
        free(lowercase);
        return false;
    }
}

/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load(const char* dictionary)
{
    FILE* dict = fopen(dictionary, "r");
    if (dict == NULL) {
        printf("Could not read dictionary file.");
        return false;
    }
    
    // declare array of char's to hold the word you want to move and index for adding letters to array
    char word[LENGTH+1];
    int index = 0; int *words = &loaded_words;
    
    for (int c = fgetc(dict); c != EOF; c = fgetc(dict))
    // BUG: once for loop reads in last letter of file, if not extra new line, it won't complete - therefore won't add last word to dict
    {
        // allow only alphabetical characters and apostrophes
        if (isalpha(c) || (c == '\'' && index > 0))
        {
            // append character to word
            word[index] = c;
            index++;
        }

        // we must have found a whole word
        else if (index > 0)
        {
            // terminate current word
            word[index] = '\0';
            
            // prepare for next word and insert current into hash table
            index = 0;
            int hash_index = hashtwo(word);
            node* newnode = malloc(sizeof(node));
            
            strcpy(newnode->word,word);
            
            if (hashtable[hash_index] != NULL) {
                newnode->next = hashtable[hash_index];
                hashtable[hash_index] = newnode;
            }
            else {
                hashtable[hash_index] = newnode;
            }
            *words += 1;
        }
        else {
            printf("ERROR");
            return false;
        }
    }
    fclose(dict);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return loaded_words;
}

/**
 * Unloads dictionary from memory.  Returns true if successful else false.
 */
bool unload(void)
{
    hashtable_free();
    return true;
}
