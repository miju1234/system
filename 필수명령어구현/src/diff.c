#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// diff 명령어: 두 파일 비교
// 옵션: -i (대소문자 무시), -q (다를 때 첫 번째 다름만 보고)
int main(int argc, char *argv[]) {
    int opt;
    int ignore_case = 0;
    int quick = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "iq")) != -1) {
        switch (opt) {
            case 'i':
                ignore_case = 1;
                break;
            case 'q':
                quick = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-i] [-q] file1 file2\n", argv[0]);
                return 1;
        }
    }

    if (optind + 1 >= argc) {
        fprintf(stderr, "Usage: %s [-i] [-q] file1 file2\n", argv[0]);
        return 1;
    }

    FILE *f1 = fopen(argv[optind], "r");
    FILE *f2 = fopen(argv[optind + 1], "r");
    if (!f1 || !f2) {
        perror("fopen");
        return 1;
    }

    int c1, c2;
    int line = 1, col = 1, diff_found = 0;

    while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF) {
        if (ignore_case) {
            c1 = tolower(c1);
            c2 = tolower(c2);
        }

        if (c1 != c2) {
            diff_found = 1;
            if (quick) {
                printf("Files differ at line %d, column %d\n", line, col);
                fclose(f1); fclose(f2);
                return 1;
            } else {
                printf("Difference at line %d, column %d: '%c' vs '%c'\n", line, col, c1, c2);
            }
        }

        if (c1 == '\n') {
            line++;
            col = 1;
        } else {
            col++;
        }
    }

    if ((c1 != EOF) || (c2 != EOF)) {
        printf("Files differ in length.\n");
        diff_found = 1;
    } else if (!diff_found) {
        printf("Files are identical.\n");
    }

    fclose(f1); fclose(f2);
    return diff_found;
}
