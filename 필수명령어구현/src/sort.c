// 22. sort.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// 파일 행 정렬 출력
int compare(const void *a, const void *b) { return strcmp(*(const char **)a, *(const char **)b); }
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r"); if (!fp) { perror("fopen"); return 1; }
    char *lines[100]; int count=0; char buf[1024];
    while (fgets(buf, sizeof(buf), fp) && count<100) lines[count++] = strdup(buf);
    qsort(lines, count, sizeof(char*), compare);
    for (int i=0; i<count; i++) printf("%s", lines[i]);
    for (int i=0; i<count; i++) free(lines[i]); fclose(fp); return 0;
}
