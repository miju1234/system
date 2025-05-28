// 8. rm.c
#include <stdio.h>
#include <unistd.h>
// 파일 삭제
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    if (unlink(argv[1]) != 0) perror("unlink"); return 0;
}
