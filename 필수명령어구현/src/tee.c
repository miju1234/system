#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// tee 명령어: 표준 출력을 파일에 동시에 저장
// 옵션: -a (파일에 추가), 기본은 덮어쓰기
int main(int argc, char *argv[]) {
    int opt;
    int append = 0;

    while ((opt = getopt(argc, argv, "a")) != -1) {
        switch (opt) {
            case 'a':
                append = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-a] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-a] file\n", argv[0]);
        return 1;
    }

    const char *filename = argv[optind];
    FILE *fp = fopen(filename, append ? "a" : "w");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    while (fgets(line, sizeof(line), stdin)) {
        fputs(line, stdout);
        fputs(line, fp);
    }

    fclose(fp);
    return 0;
}
