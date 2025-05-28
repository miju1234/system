// 50. mount.c
#include <stdio.h>
#include <sys/mount.h>
// 파일 시스템 마운트
int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <source> <target> <filesystem>\n", argv[0]);
        return 1;
    }
    if (mount(argv[1], argv[2], argv[3], 0, NULL) != 0) {
        perror("mount");
        return 1;
    }
    printf("Mounted %s on %s\n", argv[1], argv[2]);
    return 0;
}

