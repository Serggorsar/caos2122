#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    struct addrinfo *addrs = NULL;
    struct addrinfo h = {};

    h.ai_family =  AF_INET; // классический TCP/IP
    h.ai_socktype = SOCK_STREAM;

    int res = getaddrinfo(argv[1], argv[2], &h, &addrs);
    if (res < 0) {
        fprintf(stderr, "error: %s\n", gai_strerror(res));
        return 1;
    }

    for (struct addrinfo *p = addrs; p; p = p->ai_next) {
        printf("canon: %s\n", p->ai_canonname);
        struct sockaddr_in *si = (struct sockaddr_in*) p->ai_addr;
        printf("port: %d\n", ntohs(si->sin_port));
        printf("addr: %s\n", inet_ntoa(si->sin_addr));
    }

    int fd = socket(PF_INET, SOCK_STREAM, 0);

    if (connect(fd, addrs->ai_addr, addrs->ai_addrlen) < 0) {
        fprintf(stderr, "error: %s\n", strerror(errno));
        return 1;
    }

    write(fd, "GET /\r\n", sizeof("GET /\r\n") - 1);

    char c;
    int r;
    while ((r = read(fd, &c, 1)) == 1) {
        putchar(c);
    }

    freeaddrinfo(addrs);
}