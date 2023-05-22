#include "types.h"
#include "stat.h"
#include "user.h"

#define MAX_CMD_LENGTH 256
#define MAX_ARGS 3

int fork1(void) {
  int pid;

  pid = fork();
  if(pid == -1)
    return -1;
  return pid;
}

int getcmd(char *buf, int nbuf) {
  printf(2, "$ ");
  memset(buf, 0, nbuf);
  gets(buf, nbuf);
  if(buf[0] == 0) // EOF
    return -1;
  return 0;
}

void parsecmd(char* buf, char* cmd1, char* cmd2, char* cmd3) {
    int i, j;
    int count = 0;

    j = 0;
    memset(cmd1, 0, MAX_CMD_LENGTH);
    memset(cmd2, 0, MAX_CMD_LENGTH);
    memset(cmd3, 0, MAX_CMD_LENGTH);
    for (i = 0; i < strlen(buf); i++) {
        if (buf[i] != ' ' && buf[i] != '\n') {
            // 현재 문자가 공백이 아닌 경우에 문자열에 추가
            if (count == 0)
                cmd1[j] = buf[i];
            else if (count == 1)
                cmd2[j] = buf[i];
            else if (count == 2)
                cmd3[j] = buf[i];
            j++;
        } else {
            if (count == 0)
                cmd1[j] = '\0';
            else if (count == 1)
                cmd2[j] = '\0';
            else if (count == 2)
                cmd3[j] = '\0';
            // 현재 문자가 공백인 경우에 count 증가 및 다음 문자열로 이동
            if (count < 2) {
                count++;
                j = 0;
            }
        }
    }
}

int main(int argc, char *argv[]) {
    char cmd[MAX_CMD_LENGTH];
    char opcode[MAX_CMD_LENGTH], arg0[MAX_CMD_LENGTH], arg1[MAX_CMD_LENGTH];

    while (1) {
        if(getcmd(cmd, sizeof(cmd)) == 0) {
            parsecmd(cmd, opcode, arg0, arg1);
        }

        if (!strcmp(opcode, "exit"))
            break;

        else if(!strcmp(opcode, "list")) {
            // list: 현재 실행 중인 프로세스 정보 출력
            listprocs();
        }
        else if(!strcmp(opcode, "kill")) {
            // kill <pid>: pid를 가진 프로세스를 kill
            int pid = atoi(arg0);
            if(kill(pid) == 0)
                printf(1, "succeed: kill process %d\n", pid);
            else
                printf(1, "fail: cannot kill process %d\n", pid);
        }
        else if(!strcmp(opcode, "execute")) {
            // execute <path> <stacksize>: path의 경로에 위치한 프로그램을 stacksize 개수만큼의 스택용 페이지와 함께 실행
            char* path;
            strcpy(path, arg0);
            int stacksize = atoi(arg1);
            if(fork1() == 0) {
                if(exec2(path, &path, stacksize) == -1)
                    printf(1, "fail: cannot execute %s\n", path);
            }
        }
        else if(!strcmp(opcode, "memlim")) {
            // memlim <pid> <limit>: pid를 가진 프로세스의 메모리 제한을 limit으로 설정
            int pid = atoi(arg0);
            int limit = atoi(arg1);
            if(setmemorylimit(pid, limit) == 0)
                printf(1, "succeed: set memory limit of process %d to %d\n", pid, limit);
            else
                printf(1, "fail: cannot set memory limit of process %d to %d\n", pid, limit);
        }
    }
    exit();
}
