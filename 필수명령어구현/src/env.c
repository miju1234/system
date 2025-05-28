#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>

// env 명령어: 환경 변수 출력
// 옵션: -u (특정 변수 제거), -i (빈 환경에서 시작)
extern char **environ;

int main(int argc, char *argv[]) {
    int opt;
    char *unset_var = NULL;
    int ignore_env = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "u:i")) != -1) {
        switch (opt) {
            case 'u':
                unset_var = optarg;
                break;
            case 'i':
                ignore_env = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-u var] [-i]\n", argv[0]);
                return 1;
        }
    }

    if (ignore_env) {
        // 빈 환경에서 시작
        environ = NULL;
    } else if (unset_var) {
        // 특정 변수 제거
        unsetenv(unset_var);
    }

    // 환경 변수 출력
    if (environ) {
        for (char **env = environ; *env; env++) {
            printf("%s\n", *env);
        }
    }

    return 0;
}
