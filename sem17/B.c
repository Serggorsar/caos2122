#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int pipefd[2];
    if(pipe(pipefd) == -1) {
        return 1;
    }
    if(!fork()) {
        close(pipefd[0]);
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        int e = execlp(argv[1], argv[1], NULL);
        _exit(e);
    }
    if(!fork()) {
        close(pipefd[1]);
        dup2(pipefd[0], 0);
        close(pipefd[0]);
        int e = execlp(argv[2], argv[2], NULL);
        _exit(e);
    }
    close(pipefd[0]);
    close(pipefd[1]);
    wait(NULL);
    wait(NULL);
    return 0;
}
