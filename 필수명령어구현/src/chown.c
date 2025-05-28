#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <getopt.h>

// chown 명령어: 파일 소유자/그룹 변경
// 옵션: -v (verbose), -R (recursive)
int change_owner(const char *path, uid_t uid, gid_t gid, int verbose) {
    if (chown(path, uid, gid) == -1) {
        perror(path);
        return 1;
    }
    if (verbose)
        printf("ownership of '%s' changed\n", path);
    return 0;
}

#include <dirent.h>
void recursive_chown(const char *path, uid_t uid, gid_t gid, int verbose) {
    change_owner(path, uid, gid, verbose);

    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "..")) continue;

        char fullpath[1024];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        struct stat st;
        if (lstat(fullpath, &st) == 0) {
            if (S_ISDIR(st.st_mode))
                recursive_chown(fullpath, uid, gid, verbose);
            else
                change_owner(fullpath, uid, gid, verbose);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    int opt, verbose = 0, recursive = 0;
    while ((opt = getopt(argc, argv, "vR")) != -1) {
        if (opt == 'v') verbose = 1;
        else if (opt == 'R') recursive = 1;
    }

    if (optind + 2 > argc) {
        fprintf(stderr, "Usage: %s [-v] [-R] owner:group file...\n", argv[0]);
        return 1;
    }

    // 소유자와 그룹 분리
    char *owner_group = argv[optind++];
    char *colon = strchr(owner_group, ':');
    if (!colon) {
        fprintf(stderr, "Invalid format (use owner:group)\n");
        return 1;
    }
    *colon = '\0';
    char *owner = owner_group;
    char *group = colon + 1;

    struct passwd *pw = getpwnam(owner);
    struct group *gr = getgrnam(group);
    if (!pw || !gr) {
        fprintf(stderr, "Invalid user/group\n");
        return 1;
    }

    uid_t uid = pw->pw_uid;
    gid_t gid = gr->gr_gid;

    // 파일들 처리
    for (int i = optind; i < argc; i++) {
        if (recursive) {
            recursive_chown(argv[i], uid, gid, verbose);
        } else {
            change_owner(argv[i], uid, gid, verbose);
        }
    }

    return 0;
}
