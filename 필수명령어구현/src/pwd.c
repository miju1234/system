#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <getopt.h>

// pwd 명령어: 현재 작업 디렉토리 경로 출력
// 옵션: -L (심볼릭 링크 경로), -P (물리적 경로)
int main(int argc, char *argv[]) {
    int opt;
    int logical = 1;  // 기본적으로 -L

    while ((opt = getopt(argc, argv, "LP")) != -1) {
        switch (opt) {
            case 'L':
                logical = 1;
                break;
            case 'P':
                logical = 0;
                break;
            default:
                fprintf(stderr, "Usage: %s [-L|-P]\n", argv[0]);
                return 1;
        }
    }

    char cwd[PATH_MAX];
    if (logical) {
        if (getcwd(cwd, sizeof(cwd))) {
            printf("%s\n", cwd);
        } else {
            perror("getcwd");
            return 1;
        }
    } else {
        char *pwd = realpath(".", cwd);
        if (pwd) {
            printf("%s\n", cwd);
        } else {
            perror("realpath");
            return 1;
        }
    }

    return 0;
}
