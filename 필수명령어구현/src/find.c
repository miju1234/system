#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <getopt.h>

// find 명령어: 현재 디렉토리 이하에서 파일 검색
// 옵션: -name <pattern> (파일 이름 패턴 매칭), -type <f|d> (파일/디렉토리)
void search_dir(const char *path, const char *pattern, char type_filter) {
    DIR *dir = opendir(path);
    if (!dir) {
        perror(path);
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (lstat(fullpath, &st) == -1) {
            perror(fullpath);
            continue;
        }

        // 타입 필터 적용
        int type_match = 1;
        if (type_filter) {
            if (type_filter == 'f' && !S_ISREG(st.st_mode)) type_match = 0;
            else if (type_filter == 'd' && !S_ISDIR(st.st_mode)) type_match = 0;
        }

        // 이름 패턴 매칭
        int name_match = 1;
        if (pattern && strcmp(pattern, entry->d_name) != 0) name_match = 0;

        if (type_match && name_match) {
            printf("%s\n", fullpath);
        }

        if (S_ISDIR(st.st_mode)) {
            search_dir(fullpath, pattern, type_filter);
        }
    }

    closedir(dir);
}

int main(int argc, char *argv[]) {
    int opt;
    char *pattern = NULL;
    char type_filter = 0;

    while ((opt = getopt(argc, argv, "name:type:")) != -1) {
        if (strcmp(argv[optind - 1], "-name") == 0) {
            pattern = optarg;
        } else if (strcmp(argv[optind - 1], "-type") == 0) {
            if (strlen(optarg) != 1 || (optarg[0] != 'f' && optarg[0] != 'd')) {
                fprintf(stderr, "Invalid type. Use 'f' for file, 'd' for directory.\n");
                return 1;
            }
            type_filter = optarg[0];
        }
    }

    const char *start_path = (optind < argc) ? argv[optind] : ".";
    search_dir(start_path, pattern, type_filter);

    return 0;
}
