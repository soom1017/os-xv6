#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_LENGTH 128

void *thread(void *arg) {
  char ret[MAX_LENGTH];
  printf(1, "thread() entered with argument '%s'\n", arg);
  
  strcpy(ret, "This is a test");
  thread_exit(ret);

  return 0;
}

int main() {
  thread_t thid;
  void *ret;

  if (thread_create(&thid, thread, "thread 1") != 0) {
    printf(1, "pthread_create() error");
    exit();
  }

  if (thread_join(thid, &ret) != 0) {
    printf(1, "pthread_create() error");
    exit();
  }

  printf(1, "thread exited with '%s'\n", ret);
  exit();
}

