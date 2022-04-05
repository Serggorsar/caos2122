#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

struct S {
    int a;
    int b;
};
int main(int argc, char **argv) {
    if (argc < 3) {
        return 1;
    }
    int fds[2];
    if (pipe(fds) < 0) {
        return 1;
    }
    pid_t pid1;
    pid_t pid2;
    pid1 = fork();
    if (!pid1) {
        close(fds[0]);
        dup2(fds[1], STDOUT_FILENO);
        close(fds[1]);
        //raise(SIGPIPE);
        execlp(argv[1], argv[1], NULL);
        _exit(1);
    }
    pid2 = fork();
    if (!pid2) {
        close(fds[1]);
        dup2(fds[0], STDIN_FILENO);
        close(fds[0]);
        execlp(argv[2], argv[2], NULL);
        _exit(1);
    }
    close(fds[0]);
    close(fds[1]);
    int status;
    waitpid(pid1, &status, NULL);
    if (WIFSIGNALED(status)) {
        if (WTERMSIG(status) == SIGPIPE) {
            printf("%s\n", "Broken pipe");
            return 1;
        }
    }
    wait(&status);
}
