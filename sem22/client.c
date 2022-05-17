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
#include <string.h>

int main(int argc, const char**argv) {
	if (argc != 3) {
		fprintf(stderr, "too few parametrrs\n");
		exit(1);
	}
	/*struct hostent *phe;
	if (!(phe = gethostbyname(argv[1]))) {
		fprintf(stderr, "bad host name %s\n", argv[1]);
		exit(1);
	}*/
	struct addrinfo hints = {
		.ai_family = AF_INET,
		.ai_socktype = SOCK_STREAM
	};
	struct addrinfo *addrlist = NULL;
	int ret = getaddrinfo(argv[1], argv[2], &hints, &addrlist);
	if (ret) {
		fprintf(stderr, "%s\n", gai_strerror(ret));
		exit(1);
	}
	if (!addrlist) {
		fprintf(stderr, "empty addrlist\n");
		exit(1);
	}

	/*int port, n;
	if (sscanf(argv[2], "%d%n", &port, &n) != 1 ||
		argv[2][n] || port <= 0 || port >= 65536) {
		fprintf(stderr, "bad port number %s\n", argv[2]);
		exit(1);
	}*/
	int sfd;
	if ((sfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		fprintf(stderr, "error in socket creation\n");
		exit(1);
	}
	/*struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if (!phe->h_addr_list) {
		fprintf(stderr, "empty address list\n");
		exit(1);
	}
	memcpy(&sin.sin_addr, phe->h_addr_list[0], sizeof(sin.sin_addr));
	if (connect(sfd, (struct sockaddr*) &sin, sizeof(sin)) < 0) {*/
	if (connect(sfd, addrlist->ai_addr, addrlist->ai_addrlen) < 0) {
		fprintf(stderr, "error in connecting\n");
		exit(1);
	}

	time_t t = time(NULL);
	t = htonl(t);
	write(sfd, &t, sizeof(t)); // TODO

	if (read(sfd, &t, sizeof(t)) != sizeof(t)) {
		fprintf(stderr, "read failed\n");
	} else {
		t = htonl(t);
		printf("Server time: %s", ctime(&t));
	}
	close(sfd);
	return 0;
}







