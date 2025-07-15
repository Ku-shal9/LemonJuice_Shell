/*
 * command_execution.c - Implements built-in and external command handling for LemonJuice shell
 *
 * Contains function definitions for built-in commands (`cd`, `exit`, `help`, `ls`, `date`, `calc`)
 * and uses `fork` and `execvp` to launch external commands in a child process.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "shell.h"
int launch_shell(char **args)
{
    pid_t process_id, wprocess_id; // declaring process id
    int status;                    // stores the exit status of the child process
    process_id = fork();           // creating child process

    /* After Forking:
    -> child process returns 0
    -> parent process returns > 0
    -> error returns < 0 */

    if (process_id == 0) // check if we are inside child process
    {
        // execvp() -> system call that loads and executes other program inside child process
        // if error, returns -1
        if (execvp(args[0], args) == -1)
        {
            perror("lsh"); // prinitng error message
        }

        // terminating the erroneous child to not execute any unintende code
        exit(EXIT_FAILURE);
    }
    else if (process_id < 0) // error checking
    {
        perror("lsh"); // Error in forking
    }
    else // inside parent process
    {
        do
        {
            // waitpid()-> blocks the parent until the child changes state
            // passes the address of status
            // so, waitpid() -> fills the status for the process
            wprocess_id = waitpid(process_id, &status, WUNTRACED);
            // WUNTRACED -> return not only when the child exits, but if it gets stopped by a signal

        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        // WIFEXITED(status) -> returns true if child is normally termintaed
        // WIFSIGNALED -> returns true if child was terminated by a signal
    }

    return 1; // Signalling shell to continue
}

int lsh_cd(char **args)
{
    if (args[1] == NULL) // checking if user provided an argument after cd
    {
        printf("lsh: expected argumnent to \"cd\"\n"); // error message
    }
    else
    {
        // chdir -> system call to change directory
        // chdir returns 0 if successfull
        // chdir returns -1 for error
        if (chdir(args[1]) != 0) // chdir -> system call to change directory
        {
            perror("lsh"); // error message if chdir returns other than 0
        }
    }

    return 1; // green signal for shell that it should continue running
}

int lsh_exit(char **args)
{
    return 0; // when user enter exit, it should return 0 to stop the process
}

int lsh_help(char **args)
{
    // Displaying built-in help menu
    printf("\033[1;36m"); // Cyan color
    printf("MiniShell by Kushal - Help Menu\n");
    printf("The following commands are built in:\n");
    printf("  sahayog       Show this help message\n");
    printf("  paribartan [dir]   Change the current directory\n");
    printf("  niski exit       Exit the shell\n");
    printf("  jhalak ls         Show files inside the directory\n");
    printf("  samaya date       Shows the current date\n");
    printf("  shusankhya calc       Performs basic calculation + - * /\n");
    printf("\033[0m"); // Reset color

    return 1; // Signalling shell to continue
}

int lsh_ls(char **args)
{
    // Use system call to list files in current directory
    system("ls");

    return 1; // Signalling shell to continue
}

int lsh_date(char **args)
{
    // Use system show current date and time
    system("date");

    return 1; // Signalling shell to continue
}

int lsh_calc(char **args)
{
    // Ensure proper number of arguments: calc <num1> <operator> <num2>
    if (args[1] == NULL || args[2] == NULL || args[3] == NULL)
    {
        printf("Format: calc <num1> operator <num2>\n");

        return 1; // Signalling shell to continue
    }

    int x = atoi(args[1]);      // convert opearand to integer
    char operator = args[2][0]; // extracting middle operator
    int y = atoi(args[3]);      // convert second operator to integer

    switch (operator)
    {
    case '+':
        printf("Sum is: %d\n", x + y);
        break;
    case '-':
        printf("Difference is: %d\n", x - y);
        break;
    case '*':
        printf("Product is: %d\n", x * y);
        break;
    case '/':
        if (y != 0) // Prevent division by zero
            printf("Division is: %d\n", x / y);
        else
            printf("Math Error");
        break;
    default:
        printf("Unknow Operator, try + - * /");
    }

    return 1; // Signal shell to continue
}

int lsh_execute(char **args)
{
    if (args[0] == NULL)
    {
        return 1; // signal shell to continue, if empty input
    }

    // Execute Built-in commands with users input
    if (strcmp(args[0], "paribartan") == 0)
    {
        return lsh_cd(args);
    }
    if (strcmp(args[0], "nikli") == 0)
    {
        return lsh_exit(args);
    }
    if (strcmp(args[0], "sahayog") == 0)
    {
        return lsh_help(args);
    }
    if (strcmp(args[0], "jhalak") == 0)
    {
        return lsh_ls(args);
    }
    if (strcmp(args[0], "samaya") == 0)
    {
        return lsh_date(args);
    }
    if (strcmp(args[0], "shusankhya") == 0)
    {
        return lsh_calc(args);
    }

    // launch external commands
    return launch_shell(args);
}
