#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "kernel/fs.h"
#include "user/user.h"
#define MAX_BUF 512

char *fmtname(char *path)
{
  static char buf[DIRSIZ + 1];
  char *p;

  // Find first character after last slash.
  for (p = path + strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if (strlen(p) >= DIRSIZ)
    return p;
  memset(buf, 0, DIRSIZ);
  memmove(buf, p, strlen(p));
  return buf;
}

void find(char *path, char *q)
{
  int fd = open(path, O_RDONLY);
  struct stat st;
  fstat(fd, &st);
  struct dirent de;
  if (st.type == T_DIR)
  {
    while (read(fd, &de, sizeof(de)) == sizeof(de))
    {
      if (de.inum == 0)
        continue;
      if (strcmp(de.name, ".") == 0 || strcmp(de.name, "..") == 0)
        continue;
      char new_path[MAX_BUF] = {};
      strcpy(new_path, path);
      new_path[strlen(new_path)] = '/';
      strcpy(new_path + strlen(new_path), de.name);
      find(new_path, q);
    }
  }
  else
  {
    if (strcmp(fmtname(path), q) == 0)
    {
      fprintf(1, "%s\n", path);
    }
  }
  close(fd);
  return;
}

int main(int argc, char *argv[])
{
  if (argc != 3)
  {
    exit(1);
  }
  else
  {
    find(argv[1], argv[2]);
    exit(0);
  }
}
