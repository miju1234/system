// 5. cat.c
#include <stdio.h>
// 파일 내용 출력
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r"); if (!fp) { perror("fopen"); return 1; }
    int c; while ((c = fgetc(fp)) != EOF) putchar(c); fclose(fp); return 0;
}
