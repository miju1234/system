// 43. history.c
#include <stdio.h>
// 히스토리 출력
int main() {
    FILE *fp=fopen("$HOME/.bash_history","r"); if (!fp) { perror("fopen"); return 1; }
    char line[1024]; while (fgets(line,sizeof(line),fp)) printf("%s",line);
    fclose(fp); return 0;
}
