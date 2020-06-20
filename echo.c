#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        return 1;
    }
    
    int i;

    for (i = 0; i < argc; i++){
        if (i == argc -1)
        {
             printf("%s\n", argv[i]);
        } else
        {
            printf("%s", argv[i]);
        }
    }
    exit(0);
}