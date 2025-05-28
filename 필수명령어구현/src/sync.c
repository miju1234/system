#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// sync 명령어: 디스크 버퍼를 동기화
// 옵션: 없음 (기본 동작만 수행)
int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "")) != -1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    sync();
    printf("Disk buffers synced.\n");
    return 0;
}
