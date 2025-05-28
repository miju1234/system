#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// grep 명령어: 파일 내 문자열 검색
// 옵션: -i (대소문자 무시), -n (줄 번호 출력), -v (일치하지 않는 줄 출력)
int main(int argc, char *argv[]) {
    int opt;
    int ignore_case = 0;
    int show_line_number = 0;
    int invert_match = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "inv")) != -1) {
        switch (opt) {
            case 'i': ignore_case = 1; break;
            case 'n': show_line_number = 1; break;
            case 'v': invert_match = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-i] [-n] [-v] pattern file\n", argv[0]);
                return 1;
        }
    }

    if (optind + 1 >= argc) {
        fprintf(stderr, "Usage: %s [-i] [-n] [-v] pattern file\n", argv[0]);
        return 1;
    }

    char *pattern = argv[optind];
    char *filename = argv[optind + 1];

    FILE *fp = fopen(filename, "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    int line_num = 1;
    while (fgets(line, sizeof(line), fp)) {
        char *found = ignore_case ? strcasestr(line, pattern) : strstr(line, pattern);
        int match = (found != NULL);

        if (invert_match) match = !match;

        if (match) {
            if (show_line_number)
                printf("%d:", line_num);
            printf("%s", line);
        }
        line_num++;
    }

    fclose(fp);
    return 0;
}
