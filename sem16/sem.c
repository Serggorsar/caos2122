#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, char** argv) {
    if (argc < 2) {
        return 1;
    }
    int status;
    if (!fork()) {
        execlp("diff", "diff", "-y", argv[1], argv[2], NULL);
        _exit(1);
    }
    wait(&status);
    if (WIFEXITED(status)) {
        if (WEXITSTATUS(status) == 0) {
            execlp("echo", "echo", "Equal", NULL);
        }
    }
}
