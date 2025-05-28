#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// whoami 명령어: 현재 로그인한 사용자 이름 출력
// 옵션: 없음 (기본 동작만 수행)
int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "")) != -1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    char *username = getlogin();
    if (username) {
        printf("%s\n", username);
    } else {
        perror("getlogin");
        return 1;
    }

    return 0;
}
