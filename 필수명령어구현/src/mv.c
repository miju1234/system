#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// mv 명령어: 파일 이동 또는 이름 변경
// 옵션: -f (덮어쓰기)
int main(int argc, char *argv[]) {
    int opt;
    int force = 0;

    while ((opt = getopt(argc, argv, "f")) != -1) {
        switch (opt) {
            case 'f':
                force = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f] source target\n", argv[0]);
                return 1;
        }
    }

    if (optind + 2 > argc) {
        fprintf(stderr, "Usage: %s [-f] source target\n", argv[0]);
        return 1;
    }

    const char *source = argv[optind];
    const char *target = argv[optind + 1];

    if (!force) {
        if (access(target, F_OK) == 0) {
            fprintf(stderr, "Error: target '%s' already exists. Use -f to overwrite.\n", target);
            return 1;
        }
    }

    if (rename(source, target) != 0) {
        perror("rename");
        return 1;
    }

    return 0;
}
