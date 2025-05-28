// 17. file.c
#include <stdio.h>
#include <string.h>
#include <magic.h>
// 파일 유형 판별 (매직넘버 검사 추가)
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); return 1; }
    const char *filename = argv[1]; magic_t magic = magic_open(MAGIC_NONE);
    if (!magic) { fprintf(stderr, "Unable to initialize magic\n"); return 1; }
    magic_load(magic, NULL); const char *desc = magic_file(magic, filename);
    if (desc) printf("%s: %s\n", filename, desc); else fprintf(stderr, "Unable to determine type\n");
    magic_close(magic); return 0;
}
