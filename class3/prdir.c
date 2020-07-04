#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("error\n");
        return 0;
    }
    //ディレクトリ内容の読み出し
    DIR *dir;
    struct dirent *dp;
    char *path = argv[1];
    if((dir=opendir(path)) == NULL)
    {
        perror("opendir");
        exit(-1);
    }
    for(dp=readdir(dir);dp!=NULL;dp=readdir(dir))
    {
        printf("%s\n",dp->d_name);
    }
    closedir(dir);
    return 0;
}