// 23. uniq.c
#include <stdio.h>
#include <string.h>
// 중복 행 제거 출력
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r"); if (!fp) { perror("fopen"); return 1; }
    char prev[1024]="", line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (strcmp(prev, line) != 0) { printf("%s", line); strcpy(prev, line); }
    }
    fclose(fp); return 0;
}
