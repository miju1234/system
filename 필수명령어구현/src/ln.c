// 34. ln.c
#include <stdio.h>
#include <unistd.h>
// 하드 링크 또는 심볼릭 링크 생성
int main(int argc, char *argv[]) {
    if (argc < 3) {
        printf("Usage: %s <target> <linkname> [symbolic]\n", argv[0]);
        return 1;
    }
    if (argc == 4 && strcmp(argv[3], "symbolic") == 0) {
        if (symlink(argv[1], argv[2]) != 0) {
            perror("symlink");
            return 1;
        }
    } else {
        if (link(argv[1], argv[2]) != 0) {
            perror("link");
            return 1;
        }
    }
    return 0;
}
