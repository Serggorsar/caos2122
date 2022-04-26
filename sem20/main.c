#include <stdio.h>
#include <sys/eventfd.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

void event(int fd_write, int fd_read,
           int eventfd_prev, int eventfd_next) {
    for (int i = 0; i < 5; ++i) {
        uint64_t signal;
        read(eventfd_prev, &signal, sizeof(signal));

        int received;
        read(fd_read, &received, sizeof(int));
        printf("write: pid: %u, %d\n", getpid(), received);
        received = (received) % 3 + 1;
        write(fd_write, &received, sizeof(int));
        write(eventfd_next, &signal, sizeof(signal));
    }
}

int main() {
    const size_t children_num = 3;
    pid_t children[children_num];
    int eventfds[children_num];
    int pipes[2];
    if (pipe(pipes) < 0) {
        return 1;
    }
    for (size_t i = 0; i < children_num; ++i) {
        eventfds[i] = eventfd(
                i == 0 ? 1 : 0,
                EFD_SEMAPHORE
        );
    }
    for (size_t i = 0; i < children_num; ++i) {
        children[i] = fork();
        if (children[i] == -1) {
            _exit(1);
        } else if (children[i] == 0) {
            event(pipes[1],
                  pipes[0],
                  eventfds[i],
                  eventfds[(i + 1) % 3]);
            exit(0);
        }
    }
    int a = 1;
    write(pipes[1], &a, sizeof(int));
    for (int i = 0; i < children_num; ++i) {
        wait(NULL);
        close(eventfds[i]);
    }
    close(pipes[0]);
    close(pipes[1]);
    return 0;
}