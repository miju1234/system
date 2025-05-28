#include <stdio.h>
#include <time.h>
#include <getopt.h>

// date 명령어: 현재 날짜/시간 출력
// 옵션: -u (UTC로 출력), -R (RFC 2822 형식 출력)
int main(int argc, char *argv[]) {
    int opt;
    int utc = 0, rfc = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "uR")) != -1) {
        switch (opt) {
            case 'u':
                utc = 1;
                break;
            case 'R':
                rfc = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-u] [-R]\n", argv[0]);
                return 1;
        }
    }

    time_t t = time(NULL);
    struct tm *tm_info = utc ? gmtime(&t) : localtime(&t);
    char buffer[128];

    if (rfc) {
        strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S %z", tm_info);
    } else {
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", tm_info);
    }

    printf("%s\n", buffer);
    return 0;
}
