#include <stdio.h>
#include <stdlib.h>
#include <sys/mount.h>
#include <getopt.h>

// mount 명령어: 파일 시스템을 마운트
// 옵션: -t <type> (파일 시스템 유형), -o <options> (마운트 옵션)
int main(int argc, char *argv[]) {
    int opt;
    char *type = NULL;
    char *options = NULL;

    while ((opt = getopt(argc, argv, "t:o:")) != -1) {
        switch (opt) {
            case 't':
                type = optarg;
                break;
            case 'o':
                options = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-t type] [-o options] source target\n", argv[0]);
                return 1;
        }
    }

    if (optind + 2 > argc) {
        fprintf(stderr, "Usage: %s [-t type] [-o options] source target\n", argv[0]);
        return 1;
    }

    const char *source = argv[optind];
    const char *target = argv[optind + 1];

    unsigned long mountflags = 0;
    if (options && strstr(options, "ro")) mountflags |= MS_RDONLY;

    if (mount(source, target, type, mountflags, NULL) != 0) {
        perror("mount");
        return 1;
    }

    printf("Mounted %s on %s\n", source, target);
    return 0;
}
