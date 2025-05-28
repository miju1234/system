// 24. grep.c
#include <stdio.h>
#include <string.h>
// 문자열 검색 출력
int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Usage: %s <pattern> <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[2], "r"); if (!fp) { perror("fopen"); return 1; }
    char line[1024]; while (fgets(line, sizeof(line), fp))
        if (strstr(line, argv[1])) printf("%s", line);
    fclose(fp); return 0;
}
