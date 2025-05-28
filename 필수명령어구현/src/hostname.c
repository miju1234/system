// 35. hostname.c
#include <stdio.h>
#include <unistd.h>
// 호스트 이름 출력
int main() {
    char host[256]; gethostname(host,sizeof(host)); printf("%s\n",host); return 0;
}
