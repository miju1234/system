// 49. uptime.c
#include <stdio.h>
// 시스템 가동 시간 출력
int main() {
    FILE *fp=fopen("/proc/uptime","r"); if(!fp) { perror("fopen"); return 1; }
    double up; fscanf(fp,"%lf",&up); printf("Uptime: %.2f seconds\n",up); fclose(fp); return 0;
}
