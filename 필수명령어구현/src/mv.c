// 7. mv.c
#include <stdio.h>
#include <unistd.h>
// 파일 이동/이름 변경
int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Usage: %s <old> <new>\n", argv[0]); return 1; }
    if (rename(argv[1], argv[2]) != 0) perror("rename"); return 0;
}
