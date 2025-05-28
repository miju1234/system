// 1. ls.c
#include <stdio.h>
#include <dirent.h>
// 디렉토리 목록 출력
int main(int argc, char *argv[]) {
    const char *path = "."; if (argc > 1) path = argv[1];
    DIR *dir = opendir(path); if (!dir) { perror("opendir"); return 1; }
    struct dirent *entry; while ((entry = readdir(dir))) printf("%s\n", entry->d_name);
    closedir(dir); return 0;
}
