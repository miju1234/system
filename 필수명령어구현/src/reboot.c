// 48. reboot.c
#include <stdio.h>
#include <unistd.h>
#include <sys/reboot.h>
// 시스템 재부팅
int main() {
    sync();  // 데이터 동기화
    if (reboot(RB_AUTOBOOT) != 0) {
        perror("reboot");
        return 1;
    }
    return 0;
}
