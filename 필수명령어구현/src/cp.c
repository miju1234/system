// 6. cp.c
#include <stdio.h>
// 파일 복사
int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Usage: %s <src> <dest>\n", argv[0]); return 1; }
    FILE *src = fopen(argv[1], "r"); FILE *dest = fopen(argv[2], "w");
    if (!src || !dest) { perror("fopen"); return 1; }
    char buf[1024]; size_t n; while ((n = fread(buf, 1, sizeof(buf), src))) fwrite(buf, 1, n, dest);
    fclose(src); fclose(dest); return 0;
}
