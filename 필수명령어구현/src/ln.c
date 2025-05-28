#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// ln 명령어: 링크 생성
// 옵션: -s (심볼릭 링크 생성)
int main(int argc, char *argv[]) {
    int opt;
    int symbolic = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "s")) != -1) {
        switch (opt) {
            case 's':
                symbolic = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s] target link_name\n", argv[0]);
                return 1;
        }
    }

    if (optind + 1 >= argc) {
        fprintf(stderr, "Usage: %s [-s] target link_name\n", argv[0]);
        return 1;
    }

    const char *target = argv[optind];
    const char *link_name = argv[optind + 1];

    int result;
    if (symbolic) {
        result = symlink(target, link_name);
    } else {
        result = link(target, link_name);
    }

    if (result != 0) {
        perror("link");
        return 1;
    }

    return 0;
}
