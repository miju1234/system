#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// sort 명령어: 파일의 행을 정렬하여 출력
// 옵션: -r (역순 정렬)
int compare(const void *a, const void *b, int reverse) {
    return reverse ? strcmp(*(const char **)b, *(const char **)a) : strcmp(*(const char **)a, *(const char **)b);
}

int cmp_wrapper(const void *a, const void *b) {
    extern int reverse_order;
    return compare(a, b, reverse_order);
}

int reverse_order = 0;

int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "r")) != -1) {
        switch (opt) {
            case 'r':
                reverse_order = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-r] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-r] file\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[optind], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char *lines[100];
    int count = 0;
    char buf[1024];
    while (fgets(buf, sizeof(buf), fp) && count < 100) {
        lines[count++] = strdup(buf);
    }

    qsort(lines, count, sizeof(char *), cmp_wrapper);

    for (int i = 0; i < count; i++) {
        printf("%s", lines[i]);
        free(lines[i]);
    }

    fclose(fp);
    return 0;
}
