#include <stdio.h>
#include <sys/utsname.h>
#include <getopt.h>

// uname 명령어: 시스템 정보 출력
// 옵션: -a (전체 정보), -s (커널 이름), -n (네트워크 이름), -r (커널 릴리즈), -v (커널 버전), -m (머신 하드웨어 이름)
int main(int argc, char *argv[]) {
    int opt;
    int all = 0, s=0, n=0, r=0, v=0, m=0;

    while ((opt = getopt(argc, argv, "asnrvm")) != -1) {
        switch (opt) {
            case 'a': all = 1; break;
            case 's': s = 1; break;
            case 'n': n = 1; break;
            case 'r': r = 1; break;
            case 'v': v = 1; break;
            case 'm': m = 1; break;
            default:
                fprintf(stderr, "Usage: %s [-a] [-s] [-n] [-r] [-v] [-m]\n", argv[0]);
                return 1;
        }
    }

    struct utsname sys;
    uname(&sys);

    if (all || (!s && !n && !r && !v && !m)) {
        printf("%s %s %s %s %s\n", sys.sysname, sys.nodename, sys.release, sys.version, sys.machine);
    } else {
        if (s) printf("%s ", sys.sysname);
        if (n) printf("%s ", sys.nodename);
        if (r) printf("%s ", sys.release);
        if (v) printf("%s ", sys.version);
        if (m) printf("%s ", sys.machine);
        printf("\n");
    }

    return 0;
}
