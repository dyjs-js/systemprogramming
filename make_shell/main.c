#include <stdio.h>
#include <stdbool.h>

#include "run.h"

int main()
{
    char line[1024];
    char cwd[1024];
    while (1)
    {
        getcwd(cwd, sizeof(cwd));
        printf("%s $ ", cwd);
        fgets(line, sizeof(line) - 1, stdin);
        if (run(line) == false)
            break;
    }
    return 0;
}