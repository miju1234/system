#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// head 명령어: 파일의 처음 N줄 출력
// 옵션: -n <줄 수> (기본 10줄)
int main(int argc, char *argv[]) {
    int opt;
    int num_lines = 10;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                num_lines = atoi(optarg);
                if (num_lines <= 0) num_lines = 10;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n num] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n num] file\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[optind], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), fp) && count++ < num_lines) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
