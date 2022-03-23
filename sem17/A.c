#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

int main(int argc, char* argv[]) {
    int fd = open("square.py", O_WRONLY | O_TRUNC | O_CREAT, 0700);
    FILE* f = fdopen(fd, "w");
    fprintf(f, "#! /usr/bin/python3\n"
               "import os\n"
               "print((%s)**2)\n"
               "os.remove('square.py')\n",
               argv[1]);
    fclose(f);
    close(fd);
    int e = execl("square.py", "square.py", NULL);
    return e;
}
