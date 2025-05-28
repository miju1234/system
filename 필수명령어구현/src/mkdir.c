// 3. mkdir.c
#include <stdio.h>
#include <sys/stat.h>
// 디렉토리 생성
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <dir>\n", argv[0]); return 1; }
    if (mkdir(argv[1], 0755) != 0) perror("mkdir"); return 0;
}
