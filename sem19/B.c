#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/signalfd.h>
#include <sys/wait.h>

int main() {
    int fds[2];
    pipe(fds);

    sigset_t mask;
    sigemptyset(&mask);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGINT);

    if (sigprocmask(SIG_BLOCK, &mask, NULL) == -1) {
        printf("%s\n", strerror(errno));
        _exit(EXIT_FAILURE);
    }

    pid_t pid1 = fork();
    if (!pid1) {
        int sfd = signalfd(-1, &mask, 0);
        if(sfd == -1) {
            printf("1 %s\n", strerror(errno));
        }

        pid_t pid2;
        read(fds[0], &pid2, sizeof(pid_t));
        int num = 0;
        write(fds[1], &num, sizeof(num));
        kill(pid2, SIGUSR1);
        while (1) {
            struct signalfd_siginfo siginf = {};
            read(sfd, &siginf, sizeof(siginf));
            if (siginf.ssi_signo == SIGINT) {
                exit(0);
            }
            read(fds[0], &num, sizeof(num));
            ++num;
            printf("1 %d\n", num);
            write(fds[1], &num, sizeof(num));
            kill(pid2, SIGUSR1);
            if (num >= 20) {
                kill(pid2, SIGINT);
                exit(0);
            }
        }
        _exit(EXIT_FAILURE);
    }
    pid_t pid2 = fork();
    if (!pid2) {
        int sfd = signalfd(-1, &mask, 0);
        if(sfd == -1) {
            printf("2 %s\n", strerror(errno));
        }
        int num;
        while (1) {
            struct signalfd_siginfo siginf = {};
            read(sfd, &siginf, sizeof(siginf));
            if (siginf.ssi_signo == SIGINT) {
                exit(0);
            }
            read(fds[0], &num, sizeof(num));
            ++num;
            printf("2 %d\n", num);
            write(fds[1], &num, sizeof(num));
            kill(pid1, SIGUSR1);
            if (num >= 20) {
                kill(pid1, SIGINT);
                exit(0);
            }
        }
        _exit(EXIT_FAILURE);
    }
    close(fds[0]);
    write(fds[1], &pid2, sizeof(pid2));
    close(fds[1]);
    while (wait(NULL) > 0);
}
