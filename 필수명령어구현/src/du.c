#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <getopt.h>

// du 명령어: 디렉토리 사용량 출력 (재귀)
// 옵션: -h (사람이 읽기 좋은 형식), -s (총합만 출력)

void print_size(unsigned long size, int human_readable) {
    if (human_readable) {
        const char *units[] = {"B", "K", "M", "G", "T"};
        int i = 0;
        double dsize = size;
        while (dsize > 1024 && i < 4) {
            dsize /= 1024;
            i++;
        }
        printf("%.2f%s", dsize, units[i]);
    } else {
        printf("%lu", size);
    }
}

unsigned long du(const char *path, int human_readable, int summary) {
    struct stat sb;
    unsigned long total = 0;
    if (lstat(path, &sb) == 0) total += sb.st_size;

    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *entry;
        while ((entry = readdir(dir))) {
            if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
            char subpath[1024];
            snprintf(subpath, sizeof(subpath), "%s/%s", path, entry->d_name);
            struct stat st;
            if (lstat(subpath, &st) == 0) {
                if (S_ISDIR(st.st_mode))
                    total += du(subpath, human_readable, summary);
                else
                    total += st.st_size;
            }
        }
        closedir(dir);
    }

    if (!summary)
    {
        print_size(total, human_readable);
        printf("\t%s\n", path);
    }
    return total;
}

int main(int argc, char *argv[]) {
    int opt, human_readable = 0, summary = 0;
    while ((opt = getopt(argc, argv, "hs")) != -1) {
        if (opt == 'h') human_readable = 1;
        else if (opt == 's') summary = 1;
        else {
            fprintf(stderr, "Usage: %s [-h] [-s] [path]\n", argv[0]);
            return 1;
        }
    }

    const char *path = (optind < argc) ? argv[optind] : ".";

    unsigned long total = du(path, human_readable, summary);
    if (summary) {
        print_size(total, human_readable);
        printf("\t%s\n", path);
    }

    return 0;
}
