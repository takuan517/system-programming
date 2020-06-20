#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char buf[128] = "Hello,world!";
    write(1, buf, sizeof(buf));
    exit(0);
}