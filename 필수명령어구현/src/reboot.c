#include <stdio.h>
#include <stdlib.h>
#include <sys/reboot.h>
#include <unistd.h>
#include <getopt.h>

// reboot 명령어: 시스템 재부팅
// 옵션: -f (강제 재부팅)
int main(int argc, char *argv[]) {
    int opt;
    int force = 0;

    while ((opt = getopt(argc, argv, "f")) != -1) {
        switch (opt) {
            case 'f':
                force = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f]\n", argv[0]);
                return 1;
        }
    }

    // 루트 권한 확인
    if (geteuid() != 0) {
        fprintf(stderr, "Error: You must be root to reboot.\n");
        return 1;
    }

    if (sync() == -1) {
        perror("sync");
        return 1;
    }

    if (force) {
        // 강제 재부팅 (루트 권한 필요)
        if (reboot(RB_AUTOBOOT) != 0) {
            perror("reboot");
            return 1;
        }
    } else {
        printf("Rebooting system (use -f for immediate reboot)...\n");
        sleep(3);  // 사용자에게 기회를 줌
        if (reboot(RB_AUTOBOOT) != 0) {
            perror("reboot");
            return 1;
        }
    }

    return 0;
}
