// 4. rmdir.c
#include <stdio.h>
#include <unistd.h>
// 디렉토리 삭제
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <dir>\n", argv[0]); return 1; }
    if (rmdir(argv[1]) != 0) perror("rmdir"); return 0;
}
