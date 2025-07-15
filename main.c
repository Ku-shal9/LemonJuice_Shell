#include <stdio.h>
#include "shell.h"
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>

int main() // function signature
{
    char hostname[1024];
    gethostname(hostname, sizeof(hostname)); // get system hostname

    struct passwd *pw = getpwuid(getuid()); // utilize UID to get user info
    char *username = pw->pw_name;           // extract username

    printf("\033[1;32m"); // set color to bold Green
    printf("==================================== || ====================================\n");
    printf("\n");
    // printf("              Welcome %s@%s to LemonJuice  by Kushal   \n", username, hostname);
    printf("                            Type 'help' to begin         \n");
    printf("\n");
    printf("==================================== || ====================================\n");
    printf("\033[0m"); // Reset color

    shell_loop(); // calling the main shell loop

    return EXIT_SUCCESS; // indicates program exited successfully
}
