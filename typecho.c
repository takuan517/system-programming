#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char buf[128] = "";
    read(0, buf, 128);
    write(1, buf, sizeof(buf));
    exit(0);
}