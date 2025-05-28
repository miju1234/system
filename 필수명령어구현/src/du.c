// 38. du.c
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
// 디렉토리 사용량 출력 (재귀)
long du(const char *path) {
    struct stat sb; long total=0; if (stat(path,&sb)==0) total+=sb.st_size;
    DIR *dir=opendir(path); if (dir) {
        struct dirent *entry; while ((entry=readdir(dir)))
            if (strcmp(entry->d_name,".")&&strcmp(entry->d_name,"..")) {
                char buf[1024]; snprintf(buf,sizeof(buf),"%s/%s",path,entry->d_name); total+=du(buf);
            }
        closedir(dir);
    }
    return total;
}
int main(int argc, char *argv[]) {
    const char *path=argc>1?argv[1]:"."; printf("%s: %ld bytes\n",path,du(path)); return 0;
}
