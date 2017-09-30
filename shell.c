#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/stat.h>
#include <dirent.h>
#include "util.h"

#define LIMIT 256 // max number of tokens for a command
#define MAXLINE 1024 // max number of characters from user input
#define min(a, b) a<b?a:b

/**
 * Method used to print the welcome screen of our shell
 */
void welcomeScreen() {
    printf("\n\t============================================\n");
    printf("\t             Shell made by:\n");
    printf("\t--------------------------------------------\n");
    printf("\t             Abhinav Gupta - 150123001\n");
    printf("\t             Hiten Sethiya - 150123015\n");
    printf("\t             Manas Daruka - 150123020\n");
    printf("\t============================================\n");
    printf("\n\n");
}

/**
 * signal handler for SIGCHLD
 */
void signalHandler_child(int p) {
    /* Wait for all dead processes.
     * We use a non-blocking call (WNOHANG) to be sure this signal handler will not
     * block if a child was cleaned up in another part of the program. */
    while (waitpid(-1, NULL, WNOHANG) > 0) {
    }
    printf("\n");
}

/**
 * Signal handler for SIGINT
 */
void signalHandler_int(int p) {
    // We send a SIGTERM signal to the child process
    if (kill(pid, SIGTERM) == 0) {
        printf("\nProcess %d received a SIGINT signal\n", pid);
        no_reprint_prmpt = 1;
    } else {
        printf("\n");
    }
}

/**
 *	Displays the prompt for the shell
 */
void shellPrompt() {
    // We print the prompt in the form "<user>@<host> <cwd> >"
    char hostn[1204] = "";
    gethostname(hostn, sizeof(hostn));
    printf("%s > ", getcwd(currentDirectory, 1024));
}

/**
 * Method to change directory
 */
int changeDirectory(char *args[]) {
    // If we write no path (only 'cd'), then go to the home directory
    if (args[1] == NULL) {
        chdir(getenv("HOME"));
        return 1;
    }
        // Else we change the directory to the one specified by the
        // argument, if possible
    else {
        if (chdir(args[1]) == -1) {
            printf(" %s: no such directory\n", args[1]);
            return -1;
        }
    }
    return 0;
}

/**
* Method used to manage I/O redirection
*/
void fileIO(char *args[], char *inputFile, char *outputFile, int option) {

    int err = -1;

    int fileDescriptor; // between 0 and 19, describing the output or input file
    pid = fork();
    if (pid == -1) {
        printf("Child process could not be created\n");
        return;
    }
    if (pid == 0) {
        // Option 0: output redirection
        if (option == 0) {
            // We open (create) the file truncating it at 0, for write only
            fileDescriptor = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
            // We replace de standard output with the appropriate file
            dup2(fileDescriptor, STDOUT_FILENO);
            close(fileDescriptor);
            // Option 1: input and output redirection
        } else if (option == 1) {
            // We open file for read only (it's STDIN)
            fileDescriptor = open(inputFile, O_RDONLY, 0600);
            // We replace de standard input with the appropriate file
            dup2(fileDescriptor, STDIN_FILENO);
            close(fileDescriptor);
            // Same as before for the output file
            fileDescriptor = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
            dup2(fileDescriptor, STDOUT_FILENO);
            close(fileDescriptor);
        }

        setenv("parent", getcwd(currentDirectory, 1024), 1);

        if (execvp(args[0], args) == err) {
            printf("err");
            kill(getpid(), SIGTERM);
        }
    }
    waitpid(pid, NULL, 0);
}

/*
 * Remove Function */
int removeFile(char *file) {

    int ret = remove(file);

    if (ret == 0) {
        printf("File deleted successfully");
    } else {
        printf("Error: unable to delete the file");
    }

}

int removeDirectory(const char *path) {
    DIR *d = opendir(path);
    size_t path_len = strlen(path);
    int r = -1;
    if (d) {
        struct dirent *p;
        r = 0;
        while (!r && (p = readdir(d))) {
            int r2 = -1;
            char *buf;
            size_t len;
            /* Skip the names "." and ".." as we don't want to recurse on them. */
            if (!strcmp(p->d_name, ".") || !strcmp(p->d_name, "..")) {
                continue;
            }
            len = path_len + strlen(p->d_name) + 2;
            buf = malloc(len);
            if (buf) {
                struct stat statbuf;
                snprintf(buf, len, "%s/%s", path, p->d_name);
                if (!stat(buf, &statbuf)) {
                    if (S_ISDIR(statbuf.st_mode)) {
                        r2 = removeDirectory(buf);
                    } else {
                        r2 = unlink(buf);
                    }
                }
                free(buf);
            }
            r = r2;
        }
        closedir(d);
    }
    if (!r) {
        r = rmdir(path);
    }
    return r;
}

/**
* Method used to handle the commands entered via the standard input
*/
int commandHandler(char *args[]) {
    int i = 0;
    int j = 0;

    int fileDescriptor;
    int standardOut;

    int aux;

    char *args_aux[256];

    // We look for the special characters and separate the command itself
    // in a new array for the arguments
    while (args[j] != NULL) {
        if ((strcmp(args[j], ">") == 0) || (strcmp(args[j], "<") == 0) || (strcmp(args[j], "&") == 0)) {
            break;
        }
        args_aux[j] = args[j];
        j++;
    }

    // 'exit' command quits the shell
    if (strcmp(args[0], "exit") == 0) exit(0);
        // 'pwd' command prints the current directory
    else if (strcmp(args[0], "pwd") == 0) {
        if (args[j] != NULL) {
            // If we want file output
            if ((strcmp(args[j], ">") == 0) && (args[j + 1] != NULL)) {
                fileDescriptor = open(args[j + 1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
                // We replace de standard output with the appropriate file
                standardOut = dup(STDOUT_FILENO);    // first we make a copy of stdout
                // because we'll want it back
                dup2(fileDescriptor, STDOUT_FILENO);
                close(fileDescriptor);
                printf("%s\n", getcwd(currentDirectory, 1024));
                dup2(standardOut, STDOUT_FILENO);
            }
        } else {
            printf("%s\n", getcwd(currentDirectory, 1024));
        }
    }
        // 'clear' command clears the screen
    else if (strcmp(args[0], "clear") == 0) system("clear");
        // 'cd' command to change directory
    else if (strcmp(args[0], "cd") == 0) changeDirectory(args);
        // 'ls' command to list out contents of current directory
    else if (strcmp(args[0], "ls") == 0) {
        int count, i;
        struct dirent **files;
        char pathname[1000];
        getcwd(pathname, 1024);
        count = scandir(pathname, &files, NULL, alphasort);

        /* If no files found, make a non-selectable menu item */
        if (count <= 0) {
            perror("No files in this directory\n");
            return -1;
        }
        for (i = 0; i < count; ++i)
            printf("%s\n", files[i]->d_name);
    }
        /*history n : Prints the most recent n commands issued by the numbers. If n is omitted, prints all commands issued by the user.*/
    else if (strcmp(args[0], "history") == 0) {
        if (args[1]) {
            int i = 0;
            while (i < (min(atoi(args[1]), number - 1))) {
                printf("%s", history[number - 2 - i]);
                i++;
            }
        } else {
            int i = 0;
            while (i < number - 1) {
                printf("%s", history[number - 2 - i]);
                i++;
            }
        }
    } else if (strcmp(args[0], "rm") == 0) {
        char tag = NULL;
        char file[FILENAME_MAX] = {NULL};
        struct stat path_stat;
        if (args[1][0] == '-') {
            if (args[1][1]) {
                // Acquire Option type
                tag = args[1][1];
                if(args[1][2]!=NULL){printf("rm function can use only -f,-r or -v");return -1;}
                //Acquire File Path
                if (strpbrk(args[2], "/")) {
                    strcat(file, args[2]);
                }
                else {
                    getcwd(file, FILENAME_MAX);
                    strcat(file, "/");
                    strcat(file, args[2]);
                }
                //Check if path is okay
                if (stat(file, &path_stat) != 0) {
                    printf("error\n");
                    return -1;
                }
                //Option Wise operations
                if (tag == 'r') {
                    if (S_ISDIR(path_stat.st_mode))removeDirectory(file);
                    else {
                        printf("Error : Option -r requires path to be a directory.");
                        return -1;
                    }
                } else if (tag == 'f') {
                    if (!S_ISREG(path_stat.st_mode)) {
                        printf("Error : Option -f with rm requires path to be a file.");
                        return -1;
                    }
                    removeFile(file);
                } else if (tag == 'v') {
                    if (!S_ISREG(path_stat.st_mode)) {
                        printf("Error : Option -v with rm requires path to be a file.");
                        return -1;
                    }
                    printf("%s Removed", file);
                    removeFile(file);
                }
                else {
                    printf("Error : Invalid Option Specified: rm function can use only -f,-r or -v");
                    return -1;
                };
            }
        }
            //if no option is specified
        else {
            strcat(file, args[1]);
            if (stat(file, &path_stat) != 0) {
                printf("error\n");
                return -1;
            }
            if (S_ISREG(path_stat.st_mode))removeFile(file);
            else {
                printf("Error : Invalid Path");
                return -1;
            };
        }
    } else {
        // If none of the preceding commands were used, we invoke the
        // specified program. We have to detect I/O redirection.
        while (args[i] != NULL) {
            if (strcmp(args[i], "<") == 0) {
                aux = i + 1;
                if (args[aux] == NULL || args[aux + 1] == NULL || args[aux + 2] == NULL) {
                    printf("Not enough input arguments\n");
                    return -1;
                } else {
                    if (strcmp(args[aux + 1], ">") != 0) {
                        printf("Usage: Expected '>' and found %s\n", args[aux + 1]);
                        return -2;
                    }
                }
                fileIO(args_aux, args[i + 1], args[i + 3], 1);
                return 1;
            }
                // If '>' is detected, we have output redirection.
                // First we check if the structure given is the correct one,
                // and if that is the case we call the appropriate method
            else if (strcmp(args[i], ">") == 0) {
                if (args[i + 1] == NULL) {
                    printf("Not enough input arguments\n");
                    return -1;
                }
                fileIO(args_aux, NULL, args[i + 1], 0);
                return 1;
            }
            i++;
        }
    }
    return 1;
}


/**
* Main method of our shell
*/
int main(int argc, char *argv[], char **envp) {
    char line[MAXLINE]; // buffer for the user input
    char *tokens[LIMIT]; // array for the different tokens in the command
    int numTokens;

    pid = -10; // we initialize pid to an pid that is not possible

    // We call the method of initialization and the welcome screen
    //init();
    welcomeScreen();

    // We set our extern char** environ to the environment, so that
    // we can treat it later in other methods
    environ = envp;

    // We set shell=<pathname>/simple-c-shell as an environment variable for
    // the child
    setenv("shell", getcwd(currentDirectory, 1024), 1);

    // Main loop, where the user input will be read and the prompt
    // will be printed
    number = 0;
    while (TRUE) {
        // We print the shell prompt if necessary
        shellPrompt();
        // We empty the line buffer
        memset (line, '\0', MAXLINE);

        // We wait for user input
        fgets(line, MAXLINE, stdin);
        for (int i = 0; i < MAXLINE; i++) {
            history[number][i] = line[i];
        }
        // If nothing is written, the loop is executed again
        if ((tokens[0] = strtok(line, " \n\t")) == NULL) continue;
        number++;
        // We read all the tokens of the input and pass it to our
        // commandHandler as the argument
        numTokens = 1;
        // printf("%s\n", tokens[0]);
        while ((tokens[numTokens] = strtok(NULL, " \n\t")) != NULL) numTokens++;

        commandHandler(tokens);
        printf("\n");

    }

    exit(0);
}
