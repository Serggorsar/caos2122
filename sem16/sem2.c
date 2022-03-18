#include <stdio.h>
#include <fcntl.h>
#include <sys/fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void func(char *file_name) {
    if (!fork()) {
        int fd = open(file_name, O_RDONLY);
        dup2(fd, 0);
        close(fd);
        execlp("wc", "wc", NULL);
        _exit(1);
    }
}

int main(int argc, char **argv) {
    int fd = open("stats.out", O_CREAT | O_WRONLY | O_APPEND, 0664);
    dup2(fd, 1);
    close(fd);
    for (int i = 1; i != argc; ++i) {
        func(argv[i]);
        wait(NULL);
    }
}
