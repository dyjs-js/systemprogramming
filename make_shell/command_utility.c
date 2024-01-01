#include <stdbool.h>
#include <fcntl.h>
#include <stdio.h>

//help command display
_Bool display_help() {
    printf("/*************Simple shell*****************/\n");
    printf("You can use it just as conventional shell\n");
    printf("cd : change directory\n");
    printf("exit : exit this shell\n");
    printf("help : show this help\n");
    printf("/***************************************/\n");

    return true;
}

//redirection / handle
int handle_redirection(char *tokens[], int token_count)
{
    int i;
    int fd_out = 0;

    for (i = 0; i < token_count; i++)
    {
        if (strcmp(tokens[i], ">") == 0)
        {
            if (i == token_count - 1)
            {
                printf("Error : No redirection file. \n");
                return -1;
            }
            fd_out = open(tokens[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (fd_out == -1)
            {
                perror("redirection open failed");
                return - 1;
            }
            tokens[i] = NULL;
            break;
        }
    }
    return fd_out;
}
