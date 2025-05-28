#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// echo 명령어: 문자열 출력
// 옵션: -n (개행 생략), -e (이스케이프 시퀀스 해석)
void print_escaped(const char *str) {
    for (; *str; str++) {
        if (*str == '\\') {
            str++;
            switch (*str) {
                case 'n': putchar('\n'); break;
                case 't': putchar('\t'); break;
                case '\\': putchar('\\'); break;
                default: putchar(*str); break;
            }
        } else {
            putchar(*str);
        }
    }
}

int main(int argc, char *argv[]) {
    int opt;
    int no_newline = 0;
    int interpret_escapes = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "ne")) != -1) {
        switch (opt) {
            case 'n': no_newline = 1; break;
            case 'e': interpret_escapes = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-n] [-e] [string...]\n", argv[0]);
                return 1;
        }
    }

    for (int i = optind; i < argc; i++) {
        if (interpret_escapes)
            print_escaped(argv[i]);
        else
            fputs(argv[i], stdout);

        if (i < argc - 1)
            putchar(' ');
    }

    if (!no_newline)
        putchar('\n');

    return 0;
}
