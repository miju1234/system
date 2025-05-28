#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// top 명령어: 시스템 상태 모니터링 (간단)
// 옵션: -n <횟수> (업데이트 반복 횟수)
int main(int argc, char *argv[]) {
    int opt;
    int iterations = 5;

    while ((opt = getopt(argc, argv, "n:")) != -1) {
        switch (opt) {
            case 'n':
                iterations = atoi(optarg);
                if (iterations <= 0) iterations = 5;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n iterations]\n", argv[0]);
                return 1;
        }
    }

    for (int i = 0; i < iterations; i++) {
        printf("Monitoring system... (iteration %d)\n", i + 1);
        sleep(1);
    }

    return 0;
}
