#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <getopt.h>

// mkdir 명령어: 디렉토리 생성
// 옵션: -p (부모 디렉토리까지 생성), -m <mode> (권한 설정)
int main(int argc, char *argv[]) {
    int opt;
    int pflag = 0;
    mode_t mode = 0777;  // 기본 권한

    while ((opt = getopt(argc, argv, "pm:")) != -1) {
        switch (opt) {
            case 'p':
                pflag = 1;
                break;
            case 'm':
                mode = strtol(optarg, NULL, 8);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p] [-m mode] dir...\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-p] [-m mode] dir...\n", argv[0]);
        return 1;
    }

    for (int i = optind; i < argc; i++) {
        if (pflag) {
            // 부모 디렉토리까지 생성
            char *path = strdup(argv[i]);
            for (char *p = path + 1; *p; p++) {
                if (*p == '/') {
                    *p = '\0';
                    mkdir(path, mode);
                    *p = '/';
                }
            }
            mkdir(path, mode);
            free(path);
        } else {
            if (mkdir(argv[i], mode) != 0) {
                perror("mkdir");
            }
        }
    }

    return 0;
}
