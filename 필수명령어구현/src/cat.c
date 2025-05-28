#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>

// cat 명령어: 파일 내용 출력
// 옵션: -n (행 번호 출력), -E (행 끝에 $ 추가)
int main(int argc, char *argv[]) {
    int opt;
    int show_line_numbers = 0;
    int show_ends = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "nE")) != -1) {
        switch (opt) {
            case 'n':
                show_line_numbers = 1;
                break;
            case 'E':
                show_ends = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n] [-E] [file...]\n", argv[0]);
                return 1;
        }
    }

    if (optind == argc) {
        // 파일 인자 없으면 stdin 읽기
        int line = 1;
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), stdin)) {
            if (show_line_numbers)
                printf("%6d\t", line++);
            printf("%s", buffer);
            if (show_ends)
                printf("$");
        }
        return 0;
    }

    // 파일 인자 처리
    for (int i = optind; i < argc; i++) {
        FILE *fp = fopen(argv[i], "r");
        if (!fp) {
            perror(argv[i]);
            continue;
        }
        int line = 1;
        char buffer[1024];
        while (fgets(buffer, sizeof(buffer), fp)) {
            if (show_line_numbers)
                printf("%6d\t", line++);
            printf("%s", buffer);
            if (show_ends)
                printf("$");
        }
        fclose(fp);
    }

    return 0;
}
