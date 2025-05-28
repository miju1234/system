#include <stdio.h>
#include <libgen.h>
#include <string.h>
#include <getopt.h>

// dirname 명령어: 경로에서 디렉토리 추출
// 옵션: -z (출력을 널 문자로 종료)
int main(int argc, char *argv[]) {
    int opt;
    int zero_terminated = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "z")) != -1) {
        switch (opt) {
            case 'z':
                zero_terminated = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-z] path\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-z] path\n", argv[0]);
        return 1;
    }

    char *dir = dirname(argv[optind]);

    if (zero_terminated) {
        printf("%s\0", dir);
    } else {
        printf("%s\n", dir);
    }

    return 0;
}
