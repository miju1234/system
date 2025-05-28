#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <fcntl.h>
#include <errno.h>
#include <getopt.h>

// 파일 복사 함수
void copy_file(const char *src, const char *dest, int interactive) {
    if (interactive) {
        printf("Overwrite %s? (y/n): ", dest);
        char ans = getchar();
        if (ans != 'y' && ans != 'Y') return;
    }
    FILE *f_src = fopen(src, "r");
    FILE *f_dest = fopen(dest, "w");
    if (!f_src || !f_dest) { perror("fopen"); return; }
    char buf[1024];
    size_t n;
    while ((n = fread(buf, 1, sizeof(buf), f_src))) fwrite(buf, 1, n, f_dest);
    fclose(f_src); fclose(f_dest);
}

// 디렉토리 복사 함수 (재귀)
void copy_dir(const char *src, const char *dest, int interactive) {
    mkdir(dest, 0755);
    DIR *dir = opendir(src);
    if (!dir) { perror("opendir"); return; }
    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;
        char src_path[1024], dest_path[1024];
        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);
        struct stat st;
        stat(src_path, &st);
        if (S_ISDIR(st.st_mode))
            copy_dir(src_path, dest_path, interactive);
        else
            copy_file(src_path, dest_path, interactive);
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    int opt, interactive = 0, recursive = 0;
    while ((opt = getopt(argc, argv, "ir")) != -1) {
        if (opt == 'i') interactive = 1;
        else if (opt == 'r') recursive = 1;
        else {
            fprintf(stderr, "Usage: %s [-i] [-r] <src> <dest>\n", argv[0]);
            return 1;
        }
    }

    if (argc - optind < 2) {
        fprintf(stderr, "Usage: %s [-i] [-r] <src> <dest>\n", argv[0]);
        return 1;
    }

    char *src = argv[optind];
    char *dest = argv[optind + 1];
    struct stat st;
    stat(src, &st);

    if (S_ISDIR(st.st_mode)) {
        if (!recursive) {
            fprintf(stderr, "cp: omitting directory '%s'\n", src);
            return 1;
        }
        copy_dir(src, dest, interactive);
    } else {
        copy_file(src, dest, interactive);
    }

    return 0;
}
