#include <stdio.h>
#include <getopt.h>

// yes 명령어: "y" 또는 지정한 문자열을 무한 반복 출력
// 옵션: 없음 (기본 동작만 수행)
int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "")) != -1) {
        fprintf(stderr, "Usage: %s [string]\n", argv[0]);
        return 1;
    }

    const char *str = "y";
    if (optind < argc) {
        str = argv[optind];
    }

    while (1) {
        printf("%s\n", str);
    }

    return 0;
}
