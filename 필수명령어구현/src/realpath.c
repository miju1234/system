// 34. realpath.c
#include <stdio.h>
#include <stdlib.h>
// 경로의 절대경로 출력
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <path>\n", argv[0]);
        return 1;
    }
    char resolved_path[PATH_MAX];
    if (realpath(argv[1], resolved_path) != NULL) {
        printf("%s\n", resolved_path);
    } else {
        perror("realpath");
        return 1;
    }
    return 0;
}
