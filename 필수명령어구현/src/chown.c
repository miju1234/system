// 12. chown.c
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
// 소유자 변경
int main(int argc, char *argv[]) {
    if (argc != 4) { printf("Usage: %s <file> <uid> <gid>\n", argv[0]); return 1; }
    uid_t uid = atoi(argv[2]); gid_t gid = atoi(argv[3]); if (chown(argv[1], uid, gid) != 0) perror("chown");
    return 0;
}
