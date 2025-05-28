// 25. more.c
#include <stdio.h>
// 페이지 단위 출력 (간단)
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r"); if (!fp) { perror("fopen"); return 1; }
    char line[1024]; int count=0;
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line); if (++count%20==0) { printf("--More--"); getchar(); }
    }
    fclose(fp); return 0;
}
