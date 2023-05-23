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
  thread_t thid[3];
  void *ret;

  if (thread_create(&thid[0], thread, "thread 1") != 0) {
    printf(1, "pthread_create() error");
    exit();
  }
  if (thread_create(&thid[1], thread, "thread 2") != 0) {
    printf(1, "pthread_create() error");
    exit();
  }
  if (thread_create(&thid[2], thread, "thread 3") != 0) {
    printf(1, "pthread_create() error");
    exit();
  }

  if (thread_join(thid[0], &ret) != 0) {
    printf(1, "pthread_join() error");
    exit();
  }
  printf(1, "thread exited with '%s'\n", ret);

  if (thread_join(thid[1], &ret) != 0) {
    printf(1, "pthread_join() error");
    exit();
  }

  printf(1, "thread exited with '%s'\n", ret);
  if (thread_join(thid[2], &ret) != 0) {
    printf(1, "pthread_join() error");
    exit();
  }
  printf(1, "thread exited with '%s'\n", ret);

  exit();
}

