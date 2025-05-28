#include <stdio.h>
#include <fcntl.h>
#include <utime.h>
#include <stdlib.h>
#include <getopt.h>
#include <string.h>
#include <sys/stat.h>

// touch 명령어: 파일 생성 또는 타임스탬프 갱신
// 옵션: -c (존재하지 않는 파일 생성 안함), -t <timestamp> (지정 시간 설정)
int main(int argc, char *argv[]) {
    int opt;
    int no_create = 0;
    char *time_str = NULL;

    while ((opt = getopt(argc, argv, "ct:")) != -1) {
        switch (opt) {
            case 'c':
                no_create = 1;
                break;
            case 't':
                time_str = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-c] [-t timestamp] file...\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-c] [-t timestamp] file...\n", argv[0]);
        return 1;
    }

    for (int i = optind; i < argc; i++) {
        const char *filename = argv[i];
        int fd = open(filename, O_WRONLY | O_CREAT, 0644);
        if (fd == -1) {
            if (!no_create) {
                perror("open");
            }
            continue;
        }
        close(fd);

        struct utimbuf new_times;
        if (time_str) {
            struct tm tm;
            memset(&tm, 0, sizeof(tm));
            strptime(time_str, "%Y%m%d%H%M.%S", &tm);
            time_t new_time = mktime(&tm);
            new_times.actime = new_time;
            new_times.modtime = new_time;
            utime(filename, &new_times);
        } else {
            utime(filename, NULL);
        }
    }

    return 0;
}
