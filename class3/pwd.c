#include "types.h"
#include "fcntl.h"
#include "fs.h"
#include "stat.h"
#include "user.h"

#define NULL   ((void*)0)
#define false (0)
#define true (1)
#define PATH_SEPARATOR   "/"

static int getcwd(char* result)
{
    result[0] = '\0';

    char ancestor[512];
    strcpy(ancestor, ".");

    struct stat st;
    if (stat(ancestor, &st) < 0)
    return false;

    char* p = goUp(st.ino, ancestor, result);
    if (p == NULL)
    return false;
    if (result[0] == '\0')
    strcpy(result, PATH_SEPARATOR);
    return true;
}

static char* goUp(int ino, char* ancestor, char* result)
{
    strcpy(ancestor + strlen(ancestor), PATH_SEPARATOR "..");
    struct stat st;
    if (stat(ancestor, &st) < 0)
    return NULL;

    if (st.ino == ino) {
    return result;
}
char* found = NULL;
int fd = open(ancestor, O_RDONLY);
if (fd >= 0) 
{
    char* p = goUp(st.ino, ancestor, result);
    if (p != NULL) 
    {
      strcpy(p, PATH_SEPARATOR);
      p += sizeof(PATH_SEPARATOR) - 1;

      if (dirlookup(fd, ino, p))
        found = p + strlen(p);
    }
    close(fd);
}
return found;
}
static int dirlookup(int fd, int ino, char* p) {
  struct dirent de;
  while (read(fd, &de, sizeof(de)) == sizeof(de)) {
    if (de.inum == 0)
      continue;
    if (de.inum == ino) {
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = '\0';
      return true;
    }
  }
  return false;
}

int main(int argc, char *argv[])
{
    char result[512];
    result[0] = '\0';
    if (getcwd(result))
    printf(1, "%s\n", result);
    else
    printf(2, "pwd failed");
    exit();
}