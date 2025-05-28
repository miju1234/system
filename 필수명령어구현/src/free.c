#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// free 명령어: 메모리 정보 출력
// 옵션: -h (사람이 읽기 좋은 형식)
void print_size(unsigned long size, int human_readable) {
    if (human_readable) {
        const char *units[] = {"B", "K", "M", "G", "T"};
        int i = 0;
        double dsize = size;
        while (dsize > 1024 && i < 4) {
            dsize /= 1024;
            i++;
        }
        printf("%.2f%s", dsize, units[i]);
    } else {
        printf("%lu", size);
    }
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
                fprintf(stderr, "Usage: %s [-h]\n", argv[0]);
                return 1;
        }
    }

    FILE *fp = fopen("/proc/meminfo", "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    char line[256];
    unsigned long mem_total = 0, mem_free = 0, mem_available = 0, buffers = 0, cached = 0;

    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "MemTotal: %lu", &mem_total) == 1) continue;
        if (sscanf(line, "MemFree: %lu", &mem_free) == 1) continue;
        if (sscanf(line, "MemAvailable: %lu", &mem_available) == 1) continue;
        if (sscanf(line, "Buffers: %lu", &buffers) == 1) continue;
        if (sscanf(line, "Cached: %lu", &cached) == 1) continue;
    }
    fclose(fp);

    printf("              total        free        available\n");
    printf("Mem:      ");
    print_size(mem_total * 1024, human_readable);
    printf("  ");
    print_size(mem_free * 1024, human_readable);
    printf("  ");
    print_size(mem_available * 1024, human_readable);
    printf("\n");

    return 0;
}
