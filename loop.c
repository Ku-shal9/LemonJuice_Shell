/*
 * shell_loop.c - Implements the main interactive loop for LemonJuice shell
 *
 * Continuously prompts the user with hostname and current directory,
 * reads input, tokenizes commands, executes them, and manages memory.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include "shell.h"
#include <unistd.h>
#include <sys/types.h>
// #include <pwd.h>

void shell_loop()
{
    char *line;     // input from user -> heap-allocated pointer
    char **args;    // tokenized arguments
    int status = 1; // used to control loop

    char hostname[1024];
    gethostname(hostname, sizeof(hostname)); // get system hostname

    do
    {
        // cwd --> current working directory
        // step 1: Prompting the user with hostname and current working directory
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL)
        {
            printf("\033[33m%s\033[0m", hostname); // hostname -> yellow color
            printf("\033[1;34m%s\033[0m>", cwd);   // cwd -> bold blue color
        }
        else
        {
            perror("getcwd() error"); // reporting error if cwd retrieval terminates
        }

        // step 2: Read line from user's input
        line = lsh_read_line();
        printf("You typed: %s\n", line);

        // step 3: Parse the line (Tokenization)
        args = lsh_split_line(line);
        int i = 0;
        while (args[i] != 0)
        {
            printf("Token[%d]: %s\n", i, args[i]);
            i++;
        }

        // step 4 : Execute the parsed command and update the loop status
        status = lsh_execute(args);

        //  step 5: Free the allocated memory
        free(line);
        free(args);

    } while (status);
}
