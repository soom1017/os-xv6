#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "fs.h"

#define F1SIZE 12288 // 6MB = 6291456B = 12288 (blocks) * 512B
#define F2SIZE 32768 // 16MB = 16777216B = 32678 (blocks) * 512B

int
creat_test(int fd, int size)
{
  char buf[BSIZE];
  int blocks = 0;

  while(1){
    *(int*)buf = blocks;
    int cc = write(fd, buf, sizeof(buf));
    if(cc <= 0)
      break;
    blocks++;
    if (blocks % 100 == 0)
      printf(1, "%d / %d\n", blocks, size);
    if (blocks == size)
      break;
  }
  printf(1, "\nwrote %d blocks\n", blocks);
  
  close(fd);
  return blocks;
}
int
main()
{
  char buf[BSIZE];
  int fd, i, blocks;

  fd = open("f1.file", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf(1, "f1file: cannot open f1.file for writing\n");
    exit();
  }

  blocks = creat_test(fd, F1SIZE);

  fd = open("f1.file", O_RDONLY);
  if(fd < 0){
    printf(1, "f1file: cannot re-open f1.file for reading\n");
    exit();
  }
  for(i = 0; i < blocks; i++){
    int cc = read(fd, buf, sizeof(buf));
    if(cc <= 0){
      printf(1, "f1file: read error at block %d\n", i);
      exit();
    }
    if(*(int*)buf != i){
      printf(1, "f1file: read the wrong data (%d) for block %d\n",
             *(int*)buf, i);
      exit();
    }
  }
  printf(1, "f1file done; ok\n"); 

  fd = open("f2.file", O_CREATE | O_WRONLY);
  if(fd < 0){
    printf(1, "f2file: cannot open f2.file for writing\n");
    exit();
  }

  blocks = creat_test(fd, F2SIZE);

  fd = open("f2.file", O_RDONLY);
  if(fd < 0){
    printf(1, "f2file: cannot re-open f2.file for reading\n");
    exit();
  }
  for(i = 0; i < blocks; i++){
    int cc = read(fd, buf, sizeof(buf));
    if(cc <= 0){
      printf(1, "f2file: read error at block %d\n", i);
      exit();
    }
    if(*(int*)buf != i){
      printf(1, "f2file: read the wrong data (%d) for block %d\n",
             *(int*)buf, i);
      exit();
    }
  }
  printf(1, "f2file done; ok\n"); 
  exit();
}
