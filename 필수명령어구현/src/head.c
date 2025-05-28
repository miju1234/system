// 19. head.c
#include <stdio.h>
// 파일 처음 10줄 출력
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r"); if (!fp) { perror("fopen"); return 1; }
    char line[1024]; int count = 0;
    while (fgets(line, sizeof(line), fp) && count++ < 10) printf("%s", line);
    fclose(fp); return 0;
}
