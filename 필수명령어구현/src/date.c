// 31. date.c
#include <stdio.h>
#include <time.h>
// 현재 날짜/시간 출력
int main() {
    time_t t=time(NULL); struct tm *tm_info=localtime(&t);
    char buf[64]; strftime(buf,sizeof(buf),"%Y-%m-%d %H:%M:%S",tm_info);
    printf("%s\n",buf); return 0;
}
