// 13. stat.c
#include <stdio.h>
#include <sys/stat.h>
// 파일 정보 출력
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    struct stat sb; if (stat(argv[1], &sb) != 0) { perror("stat"); return 1; }
    printf("Size: %ld\n", sb.st_size); printf("Permissions: %o\n", sb.st_mode); return 0;
}
