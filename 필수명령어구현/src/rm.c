#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>

// rm 명령어: 파일 삭제
// 옵션: -r (디렉토리 재귀 삭제), -f (강제 삭제)
int remove_file(const char *path, int force) {
    if (unlink(path) != 0) {
        if (!force) perror("unlink");
        return -1;
    }
    return 0;
}

int remove_dir(const char *path, int force) {
    DIR *dir = opendir(path);
    if (!dir) {
        if (!force) perror("opendir");
        return -1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat sb;
        if (lstat(fullpath, &sb) == 0) {
            if (S_ISDIR(sb.st_mode)) {
                remove_dir(fullpath, force);
            } else {
                remove_file(fullpath, force);
            }
        }
    }
    closedir(dir);
    if (rmdir(path) != 0) {
        if (!force) perror("rmdir");
        return -1;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    int opt;
    int recursive = 0;
    int force = 0;

    while ((opt = getopt(argc, argv, "rf")) != -1) {
        switch (opt) {
            case 'r': recursive = 1; break;
            case 'f': force = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-r] [-f] file...\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-r] [-f] file...\n", argv[0]);
        return 1;
    }

    for (int i = optind; i < argc; i++) {
        struct stat sb;
        if (lstat(argv[i], &sb) != 0) {
            if (!force) perror("lstat");
            continue;
        }

        if (S_ISDIR(sb.st_mode)) {
            if (recursive) {
                remove_dir(argv[i], force);
            } else {
                fprintf(stderr, "rm: cannot remove '%s': Is a directory\n", argv[i]);
            }
        } else {
            remove_file(argv[i], force);
        }
    }

    return 0;
}
