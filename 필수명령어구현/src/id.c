#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <getopt.h>

// id 명령어: 사용자 및 그룹 ID 출력
// 옵션: -u (UID만 출력), -g (GID만 출력)
int main(int argc, char *argv[]) {
    int opt;
    int show_uid = 0, show_gid = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "ug")) != -1) {
        switch (opt) {
            case 'u': show_uid = 1; break;
            case 'g': show_gid = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-u] [-g]\n", argv[0]);
                return 1;
        }
    }

    uid_t uid = getuid();
    gid_t gid = getgid();

    if (show_uid) {
        printf("%d\n", uid);
    } else if (show_gid) {
        printf("%d\n", gid);
    } else {
        printf("UID: %d\n", uid);
        printf("GID: %d\n", gid);
    }

    return 0;
}
