#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("error\n");
        return 1;
    }
    struct stat buf;
    if (stat(argv[1], &buf) < 0)
    {
        perror("stat");
        return 0;
    }
    printf("ファイルに関する情報\n");
    printf("st_mode : %#o\n", buf.st_mode);
    printf("st_uid  : %ld\n", (long)buf.st_uid);
    printf("st_gid  : %ld\n", (long)buf.st_gid);
    printf("st_size : %ld\n", (long)buf.st_size);
    printf("st_atimespec(秒) : %ld\n", (long)buf.st_atimespec.tv_sec);
    printf("st_mtimespec(秒) : %ld\n", (long)buf.st_mtimespec.tv_sec);
    printf("st_ctimespec(秒) : %ld\n", (long)buf.st_ctimespec.tv_sec);
}