#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
#include <getopt.h>

// who 명령어: 현재 로그인 사용자 정보 출력
// 옵션: 없음 (기본 동작만 수행)
int main(int argc, char *argv[]) {
    int opt;
    while ((opt = getopt(argc, argv, "")) != -1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen("/var/run/utmp", "rb");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    struct utmp user;
    while (fread(&user, sizeof(user), 1, fp)) {
        if (user.ut_type == USER_PROCESS) {
            printf("%s\t%s\t%s\n", user.ut_user, user.ut_line, user.ut_host);
        }
    }

    fclose(fp);
    return 0;
}
