#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <strings.h>

int main(int argc, char **argv)
{
    char buf[16];
    char ebuf[32];
    int stat;
    char *cp;
    char **av;

    for (;;) {
        printf("$");
        fgets(buf, 16, stdin);

        cp = index(buf, '\n');
        *cp = '\0';

        if (fork() == 0) {
            if (execl(buf, buf, 0) < 0) {
                sprintf(ebuf, "exec: %s", buf);
                perror(ebuf);
            }
        }
        wait(&stat);
    }
}