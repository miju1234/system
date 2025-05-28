#include <stdio.h>
#include <dirent.h>
#include <getopt.h>
#include <sys/stat.h>
#include <string.h>
#include <time.h>

// ls 명령어: 디렉토리 목록 출력
// 옵션: -l (자세히 출력), -a (숨김 파일 포함)
void print_long_format(const char *path, const char *name) {
    char fullpath[1024];
    snprintf(fullpath, sizeof(fullpath), "%s/%s", path, name);
    struct stat sb;
    if (lstat(fullpath, &sb) != 0) {
        perror("lstat");
        return;
    }

    // 권한 출력
    printf( (S_ISDIR(sb.st_mode)) ? "d" : "-");
    printf( (sb.st_mode & S_IRUSR) ? "r" : "-");
    printf( (sb.st_mode & S_IWUSR) ? "w" : "-");
    printf( (sb.st_mode & S_IXUSR) ? "x" : "-");
    printf( (sb.st_mode & S_IRGRP) ? "r" : "-");
    printf( (sb.st_mode & S_IWGRP) ? "w" : "-");
    printf( (sb.st_mode & S_IXGRP) ? "x" : "-");
    printf( (sb.st_mode & S_IROTH) ? "r" : "-");
    printf( (sb.st_mode & S_IWOTH) ? "w" : "-");
    printf( (sb.st_mode & S_IXOTH) ? "x" : "-");

    printf(" %ld", sb.st_nlink);
    printf(" %d", sb.st_uid);
    printf(" %d", sb.st_gid);
    printf(" %5ld", sb.st_size);

    char timebuf[64];
    strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&sb.st_mtime));
    printf(" %s", timebuf);

    printf(" %s\n", name);
}

int main(int argc, char *argv[]) {
    int opt;
    int long_format = 0;
    int show_all = 0;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "la")) != -1) {
        switch (opt) {
            case 'l': long_format = 1; break;
            case 'a': show_all = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-l] [-a] [dir]\n", argv[0]);
                return 1;
        }
    }

    const char *path = (optind < argc) ? argv[optind] : ".";

    DIR *dir = opendir(path);
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!show_all && entry->d_name[0] == '.')
            continue;

        if (long_format)
            print_long_format(path, entry->d_name);
        else
            printf("%s\n", entry->d_name);
    }

    closedir(dir);
    return 0;
}
