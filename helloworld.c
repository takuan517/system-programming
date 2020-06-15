#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    struct tm *now;
    struct timeval total_usec;
    int year, month, day, hour, min, sec, usec;

    if(gettimeofday(&total_usec, NULL) == -1)
    {
        char buf[128] = "gettimeofday ERRNO=%d";
        write(1, buf, sizeof(buf));
        exit(0);
    }

    now = localtime(&total_usec.tv_sec);
    year = now -> tm_year + 1900;
    month = now -> tm_mon + 1;
    day = now -> tm_mday;
    hour = now -> tm_hour;
    min = now -> tm_min;
    sec = now -> tm_sec;
    usec = total_usec.tv_usec;

    char buf[128] = "Hello,world!";
    write(1, buf, sizeof(buf));
    exit(0);

    printf("%d/%02d/%02d %02d:%02d:%02d.%d\n", year, month, day, hour, min, sec, usec);
    return(0);
}