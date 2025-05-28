#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <getopt.h>

// chmod 명령어: 파일 권한 변경
// 옵션: -v (verbose, 변경된 권한 출력)
int main(int argc, char *argv[]) {
    int opt;
    int verbose = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "v")) != -1) {
        switch (opt) {
            case 'v':
                verbose = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-v] mode file...\n", argv[0]);
                return 1;
        }
    }

    if (optind + 1 >= argc) {
        fprintf(stderr, "Usage: %s [-v] mode file...\n", argv[0]);
        return 1;
    }

    // 모드 파싱
    mode_t mode = strtol(argv[optind], NULL, 8);
    if (mode == 0 && argv[optind][0] != '0') {
        perror("Invalid mode");
        return 1;
    }

    // 파일들 처리
    for (int i = optind + 1; i < argc; i++) {
        if (chmod(argv[i], mode) != 0) {
            perror(argv[i]);
        } else if (verbose) {
            printf("mode of '%s' changed to %o\n", argv[i], mode);
        }
    }

    return 0;
}
