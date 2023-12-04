#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

char buf[512];

int ans = 0;

void
cat(int fd)
{
  int n;

  while((n = read(fd, buf, sizeof(buf))) > 0) {
    if (write(1, buf, n) != n) {
      fprintf(2, "cat: write error\n");
      exit(1);
    }
    for(int i = 0; i < n; i++)
    {
      if(buf[i] == '\n')
      {
        ans += 1;
      }
    }
  }
  if(n < 0){
    fprintf(2, "cat: read error\n");
    exit(1);
  }
}

int
main(int argc, char *argv[])
{
  int fd, i;
  if(argc <= 1){
    cat(0);
    exit(0);
  }
  int flag = 0;
  if(argc == 2 && strcmp(argv[1], "-n") == 0)
  {
    flag = 1;
  }
  for(i = 1; i < argc && flag == 0; i++){
    if((fd = open(argv[i], 0)) < 0){
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
    cat(fd);
    close(fd);
  }
  if(flag == 1)
  {
    cat(0);
    printf("Number of lines : %d \n", ans);
  }
  exit(0);
}
