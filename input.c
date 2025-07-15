/*
 * input_handling.c - Implements input reading and tokenization for LemonJuice shell
 *
 * lsh_read_line: reads user input line dynamically handling buffer resizing.
 * lsh_split_line: tokenizes the input string based on defined delimiters,
 *                 dynamically expanding token array as needed.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

char *lsh_read_line(void)
{
    int buffsize = LSH_RL_BUFFSIZE; // initial buffersize for input line
    int pos = 0;                    // current position in buffer

    //  An array of characters (char[]) ->	malloc(n * sizeof(char))
    // An array of strings (char * []) -> malloc(n * sizeof(char *))

    char *buffer = malloc(sizeof(char) * buffsize); // dynamically allocating array of characters

    // checking if malloc succeeded
    if (buffer == NULL)
    {
        printf("Error in allocating!");
        return NULL;
    }

    int ch; // store each character input

    while (1) // read input character-by-character indefinitely
    {
        ch = getchar(); // Taking input character-by-character

        // Handling EOF file and new line by adding null-terminator
        if (ch == EOF || ch == '\n')
        {
            buffer[pos] = '\0'; // Append null terminator to mark string end
            return buffer;      // Return the dynamically allocated input line
        }
        else
        {
            buffer[pos] = ch; // Store the input character at current position
        }

        pos++; // move position in buffer index forward

        if (pos >= buffsize) // Handling buffer size exceeding
        {
            buffsize += LSH_RL_BUFFSIZE;        //  Expand buffer size by fixed chunk
            buffer = realloc(buffer, buffsize); // Reallocate memory to larger size

            if (buffer == NULL) // Check if realloc failed
            {
                printf("Error in allocating!");
                return NULL;
            }
        }
    }
}

char **lsh_split_line(char *line)
{
    int buffsize = LSH_TOKEN_BUFFSIZE;                 // defining the size of buffer for tokenization
    int pos = 0;                                       // counter for the token
    char **tokens = malloc(buffsize * sizeof(char *)); // Allocate array to hold token pointers

    // check if malloc succeeded
    if (tokens == NULL)
    {
        printf("Error in allocating!");
        return NULL;
    }

    char *token; // pointer to hold each individual token returned by strtok

    token = strtok(line, LSH_TOK_DELIM); // tokenization

    while (token != NULL) // loop until no more tokens are found
    {
        tokens[pos] = token; // indivdiual token is stored inside the array of tokens
        pos++;               // incremrent the position by 1

        // handling memory shortage
        if (pos >= buffsize)
        {
            buffsize += LSH_TOKEN_BUFFSIZE;                      //  Expand buffer size by fixed chunk
            tokens = realloc(tokens, buffsize * sizeof(char *)); // Reallocate memory to larger size

            // check if realloc succeeded
            if (tokens == NULL)
            {
                printf("Error in allocating!");
                return NULL;
            }
        }

        // finding the next token from the line
        token = strtok(NULL, LSH_TOK_DELIM);
    }

    tokens[pos] = NULL; // null-termination of token

    return tokens; // returns the token
}
