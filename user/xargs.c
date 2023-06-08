#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/param.h"
#include "kernel/fs.h"
#include "user/user.h"
#define MAX_BUF 32

int main(int argc, char *argv[])
{
  char ch = ' ';
  char *xargv[MAXARG];
  int xargc = argc - 1;
  char buf[512];
  for (int i = 1; i < argc; i++)
  {
    xargv[i - 1] = malloc(strlen(argv[i]));
    strcpy(xargv[i - 1], argv[i]);
  }
  while (read(0, &ch, 1) != 0)
  {
    if (ch == '\n')
    {
      xargv[xargc] = malloc(strlen(buf));
      strcpy(xargv[xargc], buf);
      xargc++;
      memset(buf, 0, sizeof(buf));
      int pid = fork();
      if (pid == 0)
      {
        exec(xargv[0], xargv);
        exit(0);
      }
      else
      {
        wait(0);
      }
      for (int i = argc - 1; i < xargc; i++)
        {
          free(xargv[i]);
          xargv[i] = 0;
        }
        xargc = argc - 1;
    }
    else
    {
      if (ch == ' ')
      {
        xargv[xargc] = malloc(strlen(buf));
        strcpy(xargv[xargc], buf);
        xargc++;
        memset(buf, 0, sizeof(buf));
      }
      else
      {
        buf[strlen(buf)] = ch;
      }
    }
  }
  exit(0);
}
