#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <unistd.h>
#include <getopt.h>

// umount 명령어: 파일 시스템 마운트 해제
// 옵션: -f (강제 해제)
int main(int argc, char *argv[]) {
    int opt;
    int force = 0;

    while ((opt = getopt(argc, argv, "f")) != -1) {
        switch (opt) {
            case 'f':
                force = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f] target\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-f] target\n", argv[0]);
        return 1;
    }

    const char *target = argv[optind];

    if (umount2(target, force ? MNT_FORCE : 0) != 0) {
        perror("umount2");
        return 1;
    }

    printf("Unmounted %s\n", target);
    return 0;
}
