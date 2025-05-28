// 15. basename.c
#include <stdio.h>
#include <libgen.h>
// 경로에서 파일 이름 추출
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <path>\n", argv[0]); return 1; }
    printf("%s\n", basename(argv[1])); return 0;
}
