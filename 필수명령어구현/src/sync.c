// 47. sync.c
#include <stdio.h>
#include <unistd.h>
// 디스크 동기화
int main() {
    sync();
    printf("Disk synchronized.\n");
    return 0;
}
