// 46. sleep.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
// 지정 시간 대기
int main(int argc,char *argv[]) {
    if(argc!=2) { printf("Usage: %s <seconds>\n", argv[0]); return 1; }
    sleep(atoi(argv[1])); return 0;
}
