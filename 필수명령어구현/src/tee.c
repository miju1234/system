// 27. tee.c
#include <stdio.h>
// 표준출력과 파일 동시 저장
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "w"); if (!fp) { perror("fopen"); return 1; }
    char line[1024]; while (fgets(line, sizeof(line), stdin)) {
        fputs(line, stdout); fputs(line, fp);
    }
    fclose(fp); return 0;
}
