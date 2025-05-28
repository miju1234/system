// 43. umount.c
#include <stdio.h>
#include <sys/mount.h>
// 파일 시스템 마운트 해제
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <target>\n", argv[0]);
        return 1;
    }
    if (umount(argv[1]) != 0) {
        perror("umount");
        return 1;
    }
    printf("Unmounted %s\n", argv[1]);
    return 0;
}
