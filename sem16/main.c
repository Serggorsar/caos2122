#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main() {
    printf("Hello, World!\n");
    if (!fork()) { // 0 1 2
        close(1);
        open("../log.txt", O_RDWR | O_CREAT | O_APPEND, 0600); // 1
//        dup2(fd, 1);
//        close(fd);

        execl("/bin/sh", "sh", "-c", "yes", NULL);
        printf("%s\n", strerror(errno));
        _exit(1);
    }
//    int status;
//    wait(&status);
//    if (WIFEXITED(status)) {
//        printf("%d", WEXITSTATUS(status));
//    }
    sleep(2);
    return 0;
}
