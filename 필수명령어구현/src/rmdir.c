#include <stdio.h>
#include <unistd.h>
#include <getopt.h>

// rmdir 명령어: 빈 디렉토리 삭제
// 옵션: -p (부모 디렉토리까지 삭제)
int main(int argc, char *argv[]) {
    int opt;
    int remove_parents = 0;

    while ((opt = getopt(argc, argv, "p")) != -1) {
        switch (opt) {
            case 'p': remove_parents = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-p] dir...\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-p] dir...\n", argv[0]);
        return 1;
    }

    for (int i = optind; i < argc; i++) {
        char *path = argv[i];
        if (rmdir(path) != 0) {
            perror("rmdir");
        } else if (remove_parents) {
            // 부모 디렉토리까지 삭제
            while ((path = strrchr(path, '/')) != NULL) {
                *path = '\0';
                if (strlen(argv[i]) == 0) break;  // 루트 디렉토리 도달
                if (rmdir(argv[i]) != 0) break;
            }
        }
    }

    return 0;
}
