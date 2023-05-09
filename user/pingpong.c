#include "kernel/types.h"
#include "user/user.h"

int main()
{
  int p[2];
  pipe(p);
  int pid = fork();
  if (pid == 0)
  {
    char c[1];
    read(p[0], c, 1);
    fprintf(0, "%d: received ping\n", getpid());
    write(p[1], "1", 1);
    close(p[0]);
    close(p[1]);
    exit(0);
  }
  else
  {
    char c[1];
    write(p[1], "0", 1);
    sleep(10);
    read(p[0], c, 1);
    fprintf(0, "%d: received pong\n", getpid());
    close(p[0]);
    close(p[1]);
    exit(0);
  }
}
