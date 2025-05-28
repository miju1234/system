#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <getopt.h>

// stat 명령어: 파일 상태 정보 출력
// 옵션: -L (심볼릭 링크 따라가기), -P (심볼릭 링크 정보 출력)
int main(int argc, char *argv[]) {
    int opt;
    int follow_symlink = 1;  // 기본 -L

    while ((opt = getopt(argc, argv, "LP")) != -1) {
        switch (opt) {
            case 'L':
                follow_symlink = 1;
                break;
            case 'P':
                follow_symlink = 0;
                break;
            default:
                fprintf(stderr, "Usage: %s [-L|-P] file\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-L|-P] file\n", argv[0]);
        return 1;
    }

    const char *file = argv[optind];
    struct stat sb;
    int ret = follow_symlink ? stat(file, &sb) : lstat(file, &sb);
    if (ret != 0) {
        perror(follow_symlink ? "stat" : "lstat");
        return 1;
    }

    printf("File: %s\n", file);
    printf("Size: %ld bytes\n", sb.st_size);
    printf("Permissions: %o\n", sb.st_mode & 0777);
    printf("Owner UID: %d\n", sb.st_uid);
    printf("Owner GID: %d\n", sb.st_gid);
    printf("Last Access: %s", ctime(&sb.st_atime));
    printf("Last Modification: %s", ctime(&sb.st_mtime));
    printf("Last Status Change: %s", ctime(&sb.st_ctime));

    return 0;
}
