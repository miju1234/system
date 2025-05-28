// 20. tail.c
#include <stdio.h>
#include <stdlib.h>
// 파일 마지막 10줄 출력
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r"); if (!fp) { perror("fopen"); return 1; }
    char *lines[10]; for (int i = 0; i < 10; i++) lines[i] = malloc(1024);
    int count = 0; while (fgets(lines[count % 10], 1024, fp)) count++;
    int start = count > 10 ? count % 10 : 0, n = count > 10 ? 10 : count;
    for (int i = 0; i < n; i++) printf("%s", lines[(start + i) % 10]);
    fclose(fp); for (int i = 0; i < 10; i++) free(lines[i]); return 0;
}
