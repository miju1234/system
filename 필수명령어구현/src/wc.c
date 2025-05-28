#include <stdio.h>
#include <ctype.h>
#include <getopt.h>

// wc 명령어: 행, 단어, 문자 수 출력
// 옵션: -l (행 수), -w (단어 수), -c (문자 수)
int main(int argc, char *argv[]) {
    int opt;
    int count_lines = 0, count_words = 0, count_chars = 0;

    while ((opt = getopt(argc, argv, "lwc")) != -1) {
        switch (opt) {
            case 'l': count_lines = 1; break;
            case 'w': count_words = 1; break;
            case 'c': count_chars = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-l] [-w] [-c] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-l] [-w] [-c] file\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[optind], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    int lines = 0, words = 0, chars = 0, inword = 0;
    char c;

    while ((c = fgetc(fp)) != EOF) {
        chars++;
        if (c == '\n') lines++;
        if (isspace(c)) inword = 0;
        else if (!inword) {
            inword = 1;
            words++;
        }
    }

    fclose(fp);

    if (!count_lines && !count_words && !count_chars) {
        printf("%d %d %d\n", lines, words, chars);
    } else {
        if (count_lines) printf("Lines: %d\n", lines);
        if (count_words) printf("Words: %d\n", words);
        if (count_chars) printf("Chars: %d\n", chars);
    }

    return 0;
}
