#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void fatal(char err[1024], bool shouldExit)
{
    printf("FATAL ERROR: %s\n", err);
    if(shouldExit == true)
    {
        exit(1);
    }
}