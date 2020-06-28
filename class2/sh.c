#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int hoge(char **cmds, int cmd_n, int index) 
{
  int pp[2];
  char *cmd = cmds[cmd_n - index -1];
  if (cmd[strlen(cmd) -1] == '\n') 
  {
    cmd[strlen(cmd) - 1] = '\0';
  }
  char *p = strtok(cmd, " ");
  char *args[128];
  int i = 0;
  while (p != NULL) 
  {
    args[i] = p;
    p = strtok(NULL, " ");
    i++;
  }
  args[i] = NULL;
  char path[256];
  // /bin以下のコマンドを取得してくる
  char commanddir[] = "/bin/";
  strcpy(path, commanddir);
  strcat(path, args[0]);
  if (i == cmd_n - 1) 
  {
    // 左端ならexecv
    execv(path, args);
  }
  else 
  {
    // 左端以外ならpipeしてforkして親が実行、子が再帰
    pipe(pp);

    if (fork() == 0) 
    {
      // 子プロセスならパイプをstdoutにdup2してdopipes(i+1)で再帰し、
      // 次のforkで親になった側が右からi+1番目のコマンドを実行
      close(pp[0]);
      dup2(pp[1], 1);
      close(pp[1]);
      hoge(cmds, cmd_n, index + 1);
    }
    else 
    {
      // 親プロセスならパイプをstdinにdup2して、
      // 右からi番目のコマンドを実行
      close(pp[1]);
      dup2(pp[0], 0);
      close(pp[0]);
      execv(path, args);
    }
  }
  //free(args);
  return 0;
}

int count(char *str, char ch) 
{
  int result = 0;
  for (int i = 0; str[i] != '\0'; i++) 
  {
    if (str[i] == ch) 
    {
      result++;
    }
  }
  return result;
}

int main(int argc, char **argv)
{
    char buf[256];

    for (;;) {
        printf("$");
        if (fgets(buf, sizeof(buf), stdin) == NULL) 
        {
            perror("error");
            return -1;
        }
        char **pipeCmds = (char **)malloc((count(buf, '|') + 1) * sizeof(char*));
        char *cmd = strtok(buf, "|");
        
        int cmdIndex = 0;
        pipeCmds[cmdIndex] = cmd;
        while (cmd != NULL) 
        {
            cmd = strtok(NULL, "|");
            cmdIndex++;
            pipeCmds[cmdIndex] = cmd;
        }
        if (fork() == 0) 
        {
            if (execl(buf, buf, 0) < 0) 
            {
                hoge(pipeCmds, cmdIndex, 0);
            }else 
            {
                wait(NULL);
            }
        }
        free(pipeCmds);
    }
}
