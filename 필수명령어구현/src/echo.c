// 10. echo.c
#include <stdio.h>
// 문자열 출력
int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) printf("%s ", argv[i]);
    printf("\n"); return 0;
}
