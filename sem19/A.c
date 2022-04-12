#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

sig_atomic_t first_flag= 0;
sig_atomic_t second_flag = 1;

void handler_1(int signal) {
    first_flag = 1;
}
void handler_2(int signal) {
    second_flag = 0;
}


int main() {
    int fds[2];
    pipe(fds);

    struct sigaction action = {};
    action.sa_handler = handler_1;
    sigaction(SIGUSR1, &action, NULL);

    action.sa_handler = handler_2;
    sigaction(SIGINT, &action, NULL);

    pid_t pid1 = fork();
    if (!pid1) {
        pid_t pid2;
        read(fds[0], &pid2, sizeof(pid_t));
        int num = 0;
        write(fds[1], &num, sizeof(num));
        kill(pid2, SIGUSR1);
        while (second_flag) {
            if (first_flag) {
                first_flag = 0;
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
        }


    }
    pid_t pid2 = fork();
    if (!pid2) {
        int num;
        while (second_flag) {
            if (first_flag) {
                first_flag = 0;
                read(fds[0], &num, sizeof(num));
                ++num;
                printf("2 %d\n", num);
                write(fds[1], &num, sizeof(num));
                kill(pid1, SIGUSR1);
            }
            if (num >= 20) {
                kill(pid1, SIGINT);
                exit(0);
            }
        }

    }
    write(fds[1], &pid2, sizeof(pid_t));
    close(fds[0]);
    close(fds[1]);
    int status;
    while (wait(&status) > 0);
}
