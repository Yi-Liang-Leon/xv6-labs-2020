#include "kernel/types.h"
#include "user/user.h"
#define MAX_BUF 512

int main()
{
  int pp[2];
  pipe(pp);
  if (fork() == 0)
  {
    while (1)
    {
      close(pp[1]);
      char p[MAX_BUF], n[MAX_BUF], w[MAX_BUF];
      if (!read(pp[0], p, 1))
      {
        exit(0);
      }
      fprintf(1, "prime %d\n", p[0]);
      int num = 0;
      while (read(pp[0], n, 1))
      {
        if (n[0] % p[0] != 0)
        {
          w[num++] = n[0];
        }
      }
      close(pp[0]);
      pipe(pp);
      for (int i = 0; i < num; i++)
      {
        write(pp[1], &w[i], 1);
      }
      if (fork() != 0)
      {
        close(pp[0]);
        close(pp[1]);
        wait(0);
        exit(0);
      }
    }
  }
  else
  {
    close(pp[0]);
    for (char i = 2; i <= 35; i++)
    {
      write(pp[1], &i, 1);
    }
    close(pp[1]);
    wait(0);
    exit(0);
  }
}
