#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>

// sleep 명령어: 지정 시간 동안 대기
// 옵션: -s <seconds> (대기 시간 초 단위), -m <milliseconds> (대기 시간 밀리초 단위)
int main(int argc, char *argv[]) {
    int opt;
    int seconds = 0;
    int milliseconds = 0;

    while ((opt = getopt(argc, argv, "s:m:")) != -1) {
        switch (opt) {
            case 's':
                seconds = atoi(optarg);
                break;
            case 'm':
                milliseconds = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-s seconds] [-m milliseconds]\n", argv[0]);
                return 1;
        }
    }

    if (seconds > 0) sleep(seconds);
    if (milliseconds > 0) usleep(milliseconds * 1000);

    return 0;
}
