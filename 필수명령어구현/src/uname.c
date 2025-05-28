// 36. uname.c
#include <stdio.h>
#include <sys/utsname.h>
// 시스템 정보 출력
int main() {
    struct utsname sys; uname(&sys);
    printf("%s %s %s %s %s\n", sys.sysname,sys.nodename,sys.release,sys.version,sys.machine);
    return 0;
}
