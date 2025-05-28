// 39. free.c
#include <stdio.h>
// 메모리 정보 출력
int main() {
    FILE *fp=fopen("/proc/meminfo","r"); if (!fp) { perror("fopen"); return 1; }
    char line[256]; while (fgets(line,sizeof(line),fp)) printf("%s",line); fclose(fp); return 0;
}
