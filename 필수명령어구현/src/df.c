// 37. df.c
#include <stdio.h>
#include <sys/statvfs.h>
// 디스크 사용량 출력
int main(int argc, char *argv[]) {
    const char *path="/"; if (argc>1) path=argv[1];
    struct statvfs buf; if (statvfs(path,&buf)!=0) { perror("statvfs"); return 1; }
    printf("Disk: %lu blocks\n", buf.f_blocks); return 0;
}
