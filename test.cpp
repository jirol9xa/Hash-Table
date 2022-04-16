#include "stdio.h"

void callPrintf()
{
    for (int i = 0; i < 10; ++i)   printf("XUI\n");
}


void callFprintf()
{
    for (int i = 0; i < 10; ++i)   fprintf(stderr, "XUI\n");
}

int main()
{
    
    callPrintf();

    callFprintf();


    return 0;
}


