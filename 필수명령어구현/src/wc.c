// 21. wc.c
#include <stdio.h>
#include <ctype.h>
// 행, 단어, 문자 수 출력
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    FILE *fp = fopen(argv[1], "r"); if (!fp) { perror("fopen"); return 1; }
    int lines=0, words=0, chars=0, inword=0; char c;
    while ((c = fgetc(fp)) != EOF) {
        chars++; if (c=='\n') lines++; if (isspace(c)) inword=0;
        else if (!inword) { inword=1; words++; }
    }
    printf("%d %d %d\n", lines, words, chars); fclose(fp); return 0;
}
