#include <stdio.h>
#include <string.h>
#include <getopt.h>

// uniq 명령어: 중복된 행 제거 출력
// 옵션: -c (중복된 행의 개수를 출력)
int main(int argc, char *argv[]) {
    int opt;
    int count_flag = 0;

    while ((opt = getopt(argc, argv, "c")) != -1) {
        switch (opt) {
            case 'c':
                count_flag = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-c] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-c] file\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[optind], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char prev[1024] = "";
    char line[1024];
    int count = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(prev, line) == 0) {
            count++;
        } else {
            if (prev[0] != '\0') {
                if (count_flag)
                    printf("%4d %s", count + 1, prev);
                else
                    printf("%s", prev);
            }
            strcpy(prev, line);
            count = 0;
        }
    }

    if (prev[0] != '\0') {
        if (count_flag)
            printf("%4d %s", count + 1, prev);
        else
            printf("%s", prev);
    }

    fclose(fp);
    return 0;
}
