// 50. which.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
// 명령어 경로 출력
int main(int argc,char *argv[]) {
    if(argc!=2) { printf("Usage: %s <command>\n", argv[0]); return 1; }
    char *path=getenv("PATH"), *dir=strtok(path,":");
    while(dir) {
        char filepath[1024]; snprintf(filepath,sizeof(filepath),"%s/%s",dir,argv[1]);
        struct stat sb; if(stat(filepath,&sb)==0) { printf("%s\n",filepath); return 0; }
        dir=strtok(NULL,":");
    }
    printf("%s not found\n",argv[1]); return 1;
}
