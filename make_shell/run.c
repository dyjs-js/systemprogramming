#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>

#include "command_utility.h"
#include "tokenize.h"

_Bool run(char *line)
{
    char *tokens[20];
    int token_count;
    pid_t child_pid;
    char delims[] = " \r\n\r";
    int i;
    
    token_count = tokenize(line, delims, tokens, sizeof(tokens) / sizeof(char *));

    // hadnling internal command sucha as cd , exit and help
    if (strcmp(tokens[0], "help") == 0)
    {
        if (tokens[1] != NULL)
        {
            fprintf(stderr, "Usage : help\n");
        }
        else
        {
            display_help();
        }
        return true;
    }

    else if (strcmp(tokens[0], "cd") == 0)
    {
        if (tokens[1] == NULL)
        {
            fprintf(stderr, "Usage : cd <directory>\n");
        }
        else
        { //디렉토리 변경 성공시 0, 실패시 -1
            if (chdir(tokens[1]) != 0)
            {
                perror("chdir failed");
            }
        }
        return true;
    }

    else if (strcmp(tokens[0], "exit") == 0)
    {
        if (tokens[1] != NULL)
        {
            fprintf(stderr, "Usage : exit\n");
        }
        else
        {
            return false;
        }
    }

    // handing redirection
    int fd_out = handle_redirection(tokens, token_count);

    // handling fork error
    if ((child_pid = fork()) < 0)
    {
        perror("fork error");
        exit(0);
    }
    // child process
    else if (child_pid == 0)
    {
        if (fd_out != -1)
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
        execvp(tokens[0], tokens);
        printf("this is child process"); // if execvp success, 실행 x
    }
    // parent process
    else
    {
        wait(); // waiting for child process
    }
    return true;
}
