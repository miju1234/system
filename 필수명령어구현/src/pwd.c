// 2. pwd.c
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
// 현재 경로 출력
int main() {
    char cwd[PATH_MAX]; if (getcwd(cwd, sizeof(cwd))) printf("%s\n", cwd);
    else perror("getcwd"); return 0;
}
