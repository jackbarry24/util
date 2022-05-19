/* ncat.c */

#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
	fprintf(stderr, "Usage: %s HOST PORT\n", argv[0]);
	return EXIT_FAILURE;
    }

    char *host = argv[1];
    char *port = argv[2];

    
    struct addrinfo *results;
    struct addrinfo  hints = {
        .ai_family   = AF_UNSPEC,
        .ai_socktype = SOCK_STREAM, 
    };
    int status;
    if ((status = getaddrinfo(host, port, &hints, &results)) != 0) {
    	fprintf(stderr, "getaddrinfo failed: %s\n", gai_strerror(status));
	return EXIT_FAILURE;
    }

    
    int socket_fd = -1;
    for (struct addrinfo *p = results; p != NULL && socket_fd < 0; p = p->ai_next) {
	
	if ((socket_fd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) < 0) {
	    fprintf(stderr, "Unable to make socket: %s\n", strerror(errno));
	    continue;
	}

	if (connect(socket_fd, p->ai_addr, p->ai_addrlen) < 0) {
	    close(socket_fd);
	    socket_fd = -1;
	    continue;
	}
    }

   
    freeaddrinfo(results);

    if (socket_fd < 0) {
	fprintf(stderr, "Unable to connect to %s:%s: %s\n", host, port, strerror(errno));
    	return EXIT_FAILURE;
    }

    printf("Connected to %s:%s\n", host, port);

   
    FILE *socket_file = fdopen(socket_fd, "w");
    if (!socket_file) {
        fprintf(stderr, "Unable to fdopen: %s\n", strerror(errno));
        close(socket_fd);
        return EXIT_FAILURE;
    }

  
    char buffer[BUFSIZ];
    while (fgets(buffer, BUFSIZ, stdin)) {
        fputs(buffer, socket_file);
    }

   
    fclose(socket_file);

    return EXIT_SUCCESS;
}

/* vim: set expandtab sts=4 sw=4 ts=8 ft=c: */
