#include <stdio.h>
#include <getopt.h>

// clear 명령어: 터미널 화면 지우기
// 옵션: -x (디버그용, clear 동작 대신 메시지 출력)
int main(int argc, char *argv[]) {
    int opt;
    int debug = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "x")) != -1) {
        switch (opt) {
            case 'x':
                debug = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-x]\n", argv[0]);
                return 1;
        }
    }

    if (debug) {
        printf("DEBUG: Clear screen (simulated)\n");
    } else {
        // ANSI 이스케이프 시퀀스로 화면 지우기
        printf("\033[H\033[J");
    }

    return 0;
}
