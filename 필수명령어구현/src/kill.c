// 29. kill.c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
// PID에 시그널 보내기
int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Usage: %s <pid> <signal>\n", argv[0]); return 1; }
    int pid=atoi(argv[1]), sig=atoi(argv[2]); if (kill(pid,sig)!=0) perror("kill");
    return 0;
}
