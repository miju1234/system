// 11. chmod.c
#include <stdio.h>
#include <sys/stat.h>
// 권한 변경
int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Usage: %s <file> <mode(octal)>\n", argv[0]); return 1; }
    mode_t mode = strtol(argv[2], NULL, 8); if (chmod(argv[1], mode) != 0) perror("chmod");
    return 0;
}
