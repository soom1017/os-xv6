#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

char buf[8192];
int stdout = 1;

void
writetest(int do_sync)
{
  int fd;
  int i;

  printf(stdout, "small file test\n");
  fd = open("small", O_CREATE|O_RDWR);
  if(fd >= 0){
    printf(stdout, "creat small succeeded; ok\n");
  } else {
    printf(stdout, "error: creat small failed!\n");
    exit();
  }
  for(i = 0; i < 512; i++){
    if(write(fd, "aaaaaaaaaa", 10) != 10){
      printf(stdout, "error: write in file failed\n");
      exit();
    }
  }
  if(do_sync)
    sync();
  printf(stdout, "write ok\n");
  close(fd);
}


int
main(int argc, char *argv[])
{
  printf(1, "synctest starting\n");

  if(!strcmp(argv[1], "sync"))
    writetest(1);
  else
    writetest(0);
  // else if(!strcmp(argv[1], "-r"))
  //   readtest();
  // printf(1, "all tests finished\n");
  exit();
}
