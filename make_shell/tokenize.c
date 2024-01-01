#include <stdio.h>


int tokenize(char *buf, char *delims, char *tokens[], int maxTokens)
{
    int token_count = 0;
    char *token = strtok(buf, delims);
    while (token != NULL && token_count < maxTokens)
    {
        tokens[token_count] = token;
        token_count++;
        token = strtok(NULL, delims);
    }
    tokens[token_count] = NULL;
    return token_count;
}
