struct schedulerlock {
  struct spinlock lock;
  int locked; // 0: UNLOCKED, 1: LOCKED
  struct proc* p;
};