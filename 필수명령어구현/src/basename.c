#include <stdio.h>
#include <libgen.h>
#include <getopt.h>

// basename 명령어: 경로에서 파일 이름 추출
// 옵션: -s (접미어 제거), -z (출력에 널 문자 사용)
int main(int argc, char *argv[]) {
    int opt;
    char *suffix = NULL;
    int zero_terminated = 0;

    // 옵션 파싱: -s, -z
    while ((opt = getopt(argc, argv, "s:z")) != -1) {
        switch (opt) {
            case 's':
                suffix = optarg;
                break;
            case 'z':
                zero_terminated = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s suffix] [-z] path\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-s suffix] [-z] path\n", argv[0]);
        return 1;
    }

    char *base = basename(argv[optind]);

    // 접미어 제거 처리
    if (suffix) {
        size_t base_len = strlen(base);
        size_t suffix_len = strlen(suffix);
        if (base_len > suffix_len && strcmp(base + base_len - suffix_len, suffix) == 0) {
            base[base_len - suffix_len] = '\0';
        }
    }

    // 출력
    if (zero_terminated)
        printf("%s\0", base);  // 널 문자 출력
    else
        printf("%s\n", base);

    return 0;
}
