#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// tail 명령어: 파일 마지막 N줄 출력
// 옵션: -n <줄 수> (기본 10줄)
int main(int argc, char *argv[]) {
    int opt;
    int lines = 10;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                lines = atoi(optarg);
                if (lines <= 0) lines = 10;
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

    char **buffer = malloc(lines * sizeof(char *));
    for (int i = 0; i < lines; i++) buffer[i] = malloc(1024);
    int count = 0;

    while (fgets(buffer[count % lines], 1024, fp)) count++;

    int start = (count >= lines) ? count % lines : 0;
    int n = (count >= lines) ? lines : count;

    for (int i = 0; i < n; i++) {
        printf("%s", buffer[(start + i) % lines]);
    }

    for (int i = 0; i < lines; i++) free(buffer[i]);
    free(buffer);
    fclose(fp);

    return 0;
}
