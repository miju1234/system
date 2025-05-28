// 9. touch.c
#include <stdio.h>
#include <fcntl.h>
#include <utime.h>
// 파일 생성/타임스탬프 갱신
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    int fd = open(argv[1], O_CREAT | O_WRONLY, 0644); if (fd == -1) { perror("open"); return 1; }
    close(fd); utime(argv[1], NULL); return 0;
}
