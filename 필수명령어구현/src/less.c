#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// less 명령어: 페이지 단위 출력 및 이전 페이지 가능 (간단)
// 옵션: -n <줄 수> (한 페이지에 출력할 줄 수)
int main(int argc, char *argv[]) {
    int opt;
    int page_size = 20;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                page_size = atoi(optarg);
                if (page_size <= 0) page_size = 20;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n lines] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n lines] file\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen(argv[optind], "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[1024];
    int count = 0;
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
        if (++count % page_size == 0) {
            printf("--Less-- (Enter to continue, q to quit): ");
            int c = getchar();
            if (c == 'q' || c == 'Q') break;
        }
    }

    fclose(fp);
    return 0;
}
