// 41. env.c
#include <stdio.h>
#include <stdlib.h>
// 환경 변수 출력
extern char **environ;
int main() { for (char **e=environ; *e; e++) printf("%s\n", *e); return 0; }
