// 14. find.c
#include <stdio.h>
#include <dirent.h>
#include <string.h>
// 파일 검색
int main(int argc, char *argv[]) {
    if (argc != 2) { printf("Usage: %s <filename>\n", argv[0]); return 1; }
    DIR *dir = opendir("."); if (!dir) { perror("opendir"); return 1; }
    struct dirent *entry; while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, argv[1]) == 0) { printf("Found: %s\n", entry->d_name); closedir(dir); return 0; }
    }
    printf("File not found.\n"); closedir(dir); return 0;
}
