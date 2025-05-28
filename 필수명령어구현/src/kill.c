#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <getopt.h>

// kill 명령어: 지정한 PID에 시그널 보내기
// 옵션: -s <signal> (시그널 번호 또는 이름 지정)
int get_signal_number(const char *sig_str) {
    if (isdigit(sig_str[0])) return atoi(sig_str);
    if (strcasecmp(sig_str, "HUP") == 0) return SIGHUP;
    if (strcasecmp(sig_str, "INT") == 0) return SIGINT;
    if (strcasecmp(sig_str, "TERM") == 0) return SIGTERM;
    if (strcasecmp(sig_str, "KILL") == 0) return SIGKILL;
    // 필요한 경우 더 많은 시그널 이름을 추가
    return -1;
}

int main(int argc, char *argv[]) {
    int opt;
    char *sig_str = "15";  // 기본 SIGTERM
    while ((opt = getopt(argc, argv, "s:")) != -1) {
        switch (opt) {
            case 's':
                sig_str = optarg;
                break;
            default:
                fprintf(stderr, "Usage: %s [-s signal] pid\n", argv[0]);
                return 1;
        }
    }

    if (optind >= argc) {
        fprintf(stderr, "Usage: %s [-s signal] pid\n", argv[0]);
        return 1;
    }

    int sig = get_signal_number(sig_str);
    if (sig == -1) {
        fprintf(stderr, "Invalid signal: %s\n", sig_str);
        return 1;
    }

    int pid = atoi(argv[optind]);
    if (kill(pid, sig) != 0) {
        perror("kill");
        return 1;
    }

    return 0;
}
