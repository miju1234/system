// 32. whoami.c
#include <stdio.h>
#include <unistd.h>
// 로그인 사용자 출력
int main() { printf("%s\n", getlogin()); return 0; }
