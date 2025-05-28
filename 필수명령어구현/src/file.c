#include <stdio.h>
#include <string.h>
#include <magic.h>
#include <getopt.h>

// file 명령어: 파일 유형 판별 (libmagic 사용)
// 옵션: -b (간단 출력), -z (압축 파일 처리 허용)
int main(int argc, char *argv[]) {
    int opt;
    int brief = 0;
    int compressed = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "bz")) != -1) {
        switch (opt) {
            case 'b':
                brief = 1;
                break;
            case 'z':
                compressed = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-b] [-z] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-b] [-z] file\n", argv[0]);
        return 1;
    }

    const char *filename = argv[optind];
    magic_t magic = magic_open(MAGIC_NONE | (compressed ? MAGIC_COMPRESS : 0));
    if (!magic) {
        fprintf(stderr, "Unable to initialize magic library\n");
        return 1;
    }

    if (magic_load(magic, NULL) != 0) {
        fprintf(stderr, "Cannot load magic database: %s\n", magic_error(magic));
        magic_close(magic);
        return 1;
    }

    const char *desc = magic_file(magic, filename);
    if (desc) {
        if (brief) {
            printf("%s\n", desc);
        } else {
            printf("%s: %s\n", filename, desc);
        }
    } else {
        fprintf(stderr, "Unable to determine file type for %s\n", filename);
    }

    magic_close(magic);
    return 0;
}
