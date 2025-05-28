// 40. id.c
#include <stdio.h>
#include <unistd.h>
// UID, GID 출력
int main() { printf("UID: %d\n", getuid()); printf("GID: %d\n", getgid()); return 0; }
