// 42. export.c
#include <stdio.h>
#include <stdlib.h>
// 환경 변수 설정
int main(int argc, char *argv[]) {
    if (argc!=2) { printf("Usage: %s VAR=VALUE\n", argv[0]); return 1; }
    putenv(argv[1]); return 0;
}
