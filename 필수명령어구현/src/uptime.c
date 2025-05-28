#include <stdio.h>
#include <getopt.h>

// uptime 명령어: 시스템 가동 시간 출력
// 옵션: 없음 (기본 동작만 수행)
int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "")) != -1) {
        fprintf(stderr, "Usage: %s\n", argv[0]);
        return 1;
    }

    FILE *fp = fopen("/proc/uptime", "r");
    if (!fp) {
        perror("fopen");
        return 1;
    }

    double uptime;
    fscanf(fp, "%lf", &uptime);
    fclose(fp);

    int hours = (int)(uptime / 3600);
    int minutes = (int)((uptime - (hours * 3600)) / 60);
    int seconds = (int)(uptime) % 60;

    printf("Uptime: %d hours %d minutes %d seconds\n", hours, minutes, seconds);
    return 0;
}
