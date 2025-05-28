#include <stdio.h>
#include <sys/statvfs.h>
#include <getopt.h>

// df 명령어: 디스크 사용량 출력
// 옵션: -h (사람이 읽기 좋은 형식)
void print_size(unsigned long size) {
    const char *units[] = {"B", "K", "M", "G", "T"};
    int i = 0;
    double dsize = size;
    while (dsize > 1024 && i < 4) {
        dsize /= 1024;
        i++;
    }
    printf("%.2f%s", dsize, units[i]);
}

int main(int argc, char *argv[]) {
    int opt;
    int human_readable = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                human_readable = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-h] [path]\n", argv[0]);
                return 1;
        }
    }

    const char *path = (optind < argc) ? argv[optind] : "/";

    struct statvfs buf;
    if (statvfs(path, &buf) != 0) {
        perror("statvfs");
        return 1;
    }

    unsigned long total = buf.f_blocks * buf.f_frsize;
    unsigned long free = buf.f_bfree * buf.f_frsize;
    unsigned long used = total - free;

    printf("Filesystem: %s\n", path);
    printf("Total: ");
    if (human_readable) print_size(total);
    else printf("%lu", total);
    printf("\nUsed: ");
    if (human_readable) print_size(used);
    else printf("%lu", used);
    printf("\nFree: ");
    if (human_readable) print_size(free);
    else printf("%lu", free);
    printf("\n");

    return 0;
}
