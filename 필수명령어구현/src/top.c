// 30. top.c
#include <stdio.h>
#include <unistd.h>
// 시스템 모니터링 (간단)
int main() {
    for (int i=0; i<5; i++) { printf("Monitoring... %d\n", i+1); sleep(1); }
    return 0;
}
