# os-xv6
os projects - modify xv6 OS (https://github.com/mit-pdos/xv6-public)
## Project 01: Implement simple scheduler on xv6
The xv6 scheduler uses "Round-Robin" policy by default. This project modifies the scheduler to "3-level MLFQ".
- 3-level consists of L0, L1, L2. 
  - L0 queue gets the highest priority.
  - Each level's time quantum: Ln = 2n+4 ticks.
- To prevent starvation, priority boosting occurs once every 100 global ticks.
  - All processes are rescheduled to the L0 queue.
- There may be processes that should always be prioritized over those scheduled by the MLFQ scheduler.
  - 2 system calls `schedulerLock()`, `schedulerUnlock()` are implemented.
  - If there is a process that locks the scheduler, the MLFQ scheduler will not work, and the process will be scheduled first.

## Project 02: Implement process manager and threading (LWP)
The xv6 os does not provide threading and process management. This project improves xv6 by adding these features.
- process manager
  - The xv6 allocates one stack page when `exec` called. System call `exec2` in this project allocates various size of stack (1 to 100 stack pages).
  - System call `setmemorylimit` limits the maximum amount of memory that can be allocated for a particular process.
  - User program "pmanager" supports process managing functions
    - `list` - Outputs information about currently running processes
    - `kill` - Kill a process with the pid
    - `execute` - Run the program with specified stacksize
    - `memlim` - set the program's memory limit
    - `exit`

- Threading (LWP, light-weight process)
  - Like pthread in Unix, this project provides threading APIs.
  - `thread_create`, `thread_exit`, `thread_join`

## Project 03: Improve file system on xv6
- multi indirect
  - The xv6 stores file data through direct and single indirect method, which limits file write to 140 blocks (70KB) max.
  - This project adds multi indirect, so that created file has 10 direct (10 blocks), 1 single indirect (128 blocks), 1 double direct (128 * 128 blocks), and 1 triple indirect (128 * 128 * 128 blocks).
  - Resulting maximum file size will be 2,113,674 blocks.
- symbolic link
  - The xv6 supports hard link, not symbolic link.
  - This project implements symbolic link on xv6, so you can create shortcuts that are not dependent to the original file.
  - `ln [-s]` creates symbolic link.
- sync
  - The xv6 performs group flush for write operation. This approach degrades performance when a particular process generates a large number of write operations.
  - Instead, modified xv6 performs "Buffered I/O", which does not flush data by default.
  - Only flushes data when the system call `sync` called, and when the buffer is full (current buffer size = 10 * 3 * 512B).
