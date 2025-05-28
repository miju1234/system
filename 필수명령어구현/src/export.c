#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// export 명령어: 환경 변수 설정
// 옵션: -n (변수 제거)
int main(int argc, char *argv[]) {
    int opt;
    int remove_var = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "n")) != -1) {
        switch (opt) {
            case 'n':
                remove_var = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-n] VAR=VALUE | VAR\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-n] VAR=VALUE | VAR\n", argv[0]);
        return 1;
    }

    char *var = argv[optind];

    if (remove_var) {
        // 환경 변수 제거
        if (unsetenv(var) != 0) {
            perror("unsetenv");
            return 1;
        }
    } else {
        // VAR=VALUE 처리
        char *eq = strchr(var, '=');
        if (eq) {
            if (putenv(var) != 0) {
                perror("putenv");
                return 1;
            }
        } else {
            // VAR만 지정한 경우, 값이 없는 변수 설정
            char temp[256];
            snprintf(temp, sizeof(temp), "%s=", var);
            if (putenv(temp) != 0) {
                perror("putenv");
                return 1;
            }
        }
    }

    return 0;
}
