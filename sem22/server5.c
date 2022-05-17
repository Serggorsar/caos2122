#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <time.h>
#include <netinet/in.h>
#include <poll.h>

enum { MAX_CLIENTS = 10, BUF_SIZE = 256 };


int main(int argc, const char**argv) {
    if (argc != 2) {
        fprintf(stderr, "%s\n", "too few parameters");
        exit(1);
    }
    int port, n;
    if (sscanf(argv[1], "%d%n", &port, &n) != 1 ||
            argv[1][n] || port <= 0 || port > 65535) {
        fprintf(stderr, "%s\n", "invalid port number");
        exit(1);
    }
    int lfd, afd;
    if ((lfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "%s\n", "error in socket creating");
        exit(1);
    }
    int val = 1;
    setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));
    setsockopt(lfd, SOL_SOCKET, SO_REUSEPORT, &val, sizeof(val));

    struct sockaddr_in aaddr, baddr;
    baddr.sin_family = AF_INET;
    baddr.sin_port = htons(port);
    baddr.sin_addr.s_addr = INADDR_ANY;

    if(bind(lfd, (struct sockaddr *)&baddr, sizeof(baddr)) < 0) {
        fprintf(stderr, "%s\n", "error in bind");
        close(lfd);
        exit(1);
    }

    if(listen(lfd, 5) < 0) {
        fprintf(stderr, "%s\n", "error in listen");
        close(lfd);
        exit(1);
    } 

    struct pollfd pollfds[MAX_CLIENTS + 1];
    pollfds[0].fd = lfd;
    pollfds[0].events = POLLIN | POLLPRI;
    int useClient = 0;
    while(1) {
        printf("clients %d\n", useClient);
        int ret = poll(pollfds, useClient + 1, 5000);
        if (ret > 0) {
            if (pollfds[0].revents & POLLIN) {
                struct sockaddr_in client_addr;
                int addrlen = sizeof(client_addr);
                int client_socket = accept(lfd, 
                    (struct sockaddr*) &client_addr,
                    (socklen_t*) &addrlen);
                printf("accept success %s\n", inet_ntoa(client_addr.sin_addr));
                for (int i = 1; i < MAX_CLIENTS + 1; ++i) {
                    if (pollfds[i].fd == 0) {
                        pollfds[i].fd = client_socket;
                        pollfds[i].events = POLLIN;
                        useClient++;
                        break;
                    }
                }
            }
            for (int i = 1; i < MAX_CLIENTS + 1; ++i) {
                if (pollfds[i].fd > 0 && pollfds[i].revents && POLLIN) {
                    char buf[BUF_SIZE];
                    int readed = read(pollfds[i].fd, buf, BUF_SIZE - 1);
                    if (readed == -1 || readed == 0) {
                        close(pollfds[i].fd);
                        pollfds[i].fd = 0;
                        pollfds[i].events = 0;
                        pollfds[i].revents = 0;
                        useClient--;
                    } else {
                        buf[readed] = 0;
                        printf("get %s\n", buf);
                    }
                }
            }
        }

    }
    close(lfd);
}