// 33. who.c
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <unistd.h>
// 현재 로그인 사용자 정보 출력
int main() {
    struct utmp user; FILE *fp=fopen("/var/run/utmp","rb");
    if (!fp) { perror("fopen"); return 1; }
    while (fread(&user,sizeof(user),1,fp))
        if (user.ut_type==USER_PROCESS) printf("%s\t%s\n",user.ut_user,user.ut_line);
    fclose(fp); return 0;
}
