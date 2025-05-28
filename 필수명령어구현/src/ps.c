#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <getopt.h>

// ps 명령어: 현재 프로세스 목록 출력
// 옵션: -f (자세히 출력)
void print_details(const char *pid) {
    char path[1024], line[256];
    snprintf(path, sizeof(path), "/proc/%s/status", pid);
    FILE *fp = fopen(path, "r");
    if (!fp) return;

    printf("PID: %s ", pid);
    while (fgets(line, sizeof(line), fp)) {
        if (strncmp(line, "Name:", 5) == 0) {
            printf("%s", line);
            break;
        }
    }
    fclose(fp);
}

int main(int argc, char *argv[]) {
    int opt;
    int full_format = 0;

    while ((opt = getopt(argc, argv, "f")) != -1) {
        switch (opt) {
            case 'f':
                full_format = 1;
                break;
            default:
                fprintf(stderr, "Usage: %s [-f]\n", argv[0]);
                return 1;
        }
    }

    DIR *dir = opendir("/proc");
    if (!dir) {
        perror("opendir");
        return 1;
    }

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (isdigit(entry->d_name[0])) {
            if (full_format) {
                print_details(entry->d_name);
            } else {
                printf("%s\n", entry->d_name);
            }
        }
    }

    closedir(dir);
    return 0;
}
