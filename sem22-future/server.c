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
    int alen;
    time_t ct, st;
    while(1) {
    	alen = sizeof(aaddr);
    	if((afd = accept(lfd, (struct sockaddr*) &aaddr, (socklen_t *) &alen)) < 0) {
    		fprintf(stderr, "%s\n", "error in accept");
    	}
    	int pid;
    	if((pid = fork()) < 0) {
    		fprintf(stderr, "%s\n", "error in fork");
    	} else if (!pid) {
    		close(lfd);
        	printf("%d: connection from %s:%d accepted\n", 
        		getpid(), inet_ntoa(aaddr.sin_addr), ntohs(aaddr.sin_port));

            // sleep(10);
        	if (read(afd, &ct, sizeof(ct)) != sizeof(ct)) {
        		fprintf(stderr, "%s\n", "error in read");
        	} else {
        		ct = ntohl(ct);
        		st = time(NULL);
        		printf("%d, client time %lu, server time %lu\n", 
        			getpid(), ct, st);
        		st = htonl(st);
        		write(afd, &st, sizeof(st));
        	}
        	close(afd);
    	    exit(0);
	    }
    }
    close(afd);
    close(lfd);
    return 0;
}