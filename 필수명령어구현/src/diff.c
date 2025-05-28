// 18. diff.c
#include <stdio.h>
#include <string.h>
// 두 파일 비교
int main(int argc, char *argv[]) {
    if (argc != 3) { printf("Usage: %s <file1> <file2>\n", argv[0]); return 1; }
    FILE *f1 = fopen(argv[1], "r"), *f2 = fopen(argv[2], "r");
    if (!f1 || !f2) { perror("fopen"); return 1; }
    int c1, c2; while ((c1 = fgetc(f1)) != EOF && (c2 = fgetc(f2)) != EOF)
        if (c1 != c2) { printf("Files differ.\n"); fclose(f1); fclose(f2); return 1; }
    if ((c1 != EOF) || (c2 != EOF)) printf("Files differ in length.\n");
    else printf("Files are identical.\n");
    fclose(f1); fclose(f2); return 0;
}
