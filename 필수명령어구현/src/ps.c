// 28. ps.c
#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
// 현재 프로세스 목록 출력
int main() {
    DIR *dir = opendir("/proc"); if (!dir) { perror("opendir"); return 1; }
    struct dirent *entry; while ((entry = readdir(dir)))
        if (isdigit(entry->d_name[0])) printf("%s\n", entry->d_name);
    closedir(dir); return 0;
}
