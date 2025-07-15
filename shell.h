#ifndef SHELL_H
#define SHELL_H

/*
 * shell.h - Header file for LemonJuice shell
 *
 * Defines constants, function prototypes, and delimiters
 * used for reading, parsing, and executing shell commands.
 */

#define LSH_RL_BUFFSIZE 1024
// -> number of tokens that our parser can take when parsing one input line
#define LSH_TOKEN_BUFFSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"
// -> defines the set of delimeters that are used when tokenizing the input string
/*

 * (space) -> space
 * \t -> tab space
 * \r -> carriage return -> line endings
 * \n -> new line
 * \a -> alert

 */

char *lsh_read_line(void);         // Read line from user input
char **lsh_split_line(char *line); // Split line into tokens
int launch_shell(char **args);     // launch a shell program with provided commands
int lsh_execute(char **args);      // execute shell built-in commands
int lsh_cd(char **args);           // built-in to change directory
int lsh_exit(char **args);         // built-in to exit the shell
int lsh_help(char **args);         // built-in to display help information
int lsh_ls(char **args);           // built-in to display the contents of directory
int lsh_date(char **args);         // built-in to display current date and time
int lsh_calc(char **args);         // built-in for performing simple calculation
void shell_loop();                 // main loop to process shell commands

#endif
