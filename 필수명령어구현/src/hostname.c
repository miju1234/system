#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// hostname 명령어: 시스템 호스트 이름 출력/설정
// 옵션: -s (짧은 이름 출력), -h (호스트 이름 설정)
int main(int argc, char *argv[]) {
    int opt;
    int short_name = 0;
    char *new_name = NULL;

    // 옵션 파싱
    while ((opt = getopt(argc, argv, "sh:")) != -1) {
        switch (opt) {
            case 's': short_name = 1; break;
            case 'h': new_name = optarg; break;
            default:
                fprintf(stderr, "Usage: %s [-s] [-h name]\n", argv[0]);
                return 1;
        }
    }

    char hostname[256];

    if (new_name) {
        if (sethostname(new_name, strlen(new_name)) != 0) {
            perror("sethostname");
            return 1;
        }
        printf("Hostname set to %s\n", new_name);
    } else {
        if (gethostname(hostname, sizeof(hostname)) != 0) {
            perror("gethostname");
            return 1;
        }
        if (short_name) {
            char *dot = strchr(hostname, '.');
            if (dot) *dot = '\0';
        }
        printf("%s\n", hostname);
    }

    return 0;
}
