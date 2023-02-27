#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
	struct addrinfo hints,*server;
	struct sockaddr client;
	socklen_t client_size;
	int r,sockfd;
	const char *buffer = "UDP Server says \"Hello!\"\n";
	const int size = 1024;
	char input[size];

	/* configure the server */
	memset(&hints, 0, sizeof(hints));	/* use memset_s() */
	hints.ai_family = AF_INET;			/* IPv4 connection */
	hints.ai_socktype = SOCK_DGRAM;		/* UDP, datagram */
	hints.ai_flags = AI_PASSIVE;		/* accept any connection */
	r = getaddrinfo(0, "8080", &hints, &server);	/* 0==localhost */
	if( r!=0 )
	{
		perror("failed");
		exit(1);
	}

	/* create the socket */
	sockfd = socket(server->ai_family,server->ai_socktype,server->ai_protocol);
	if( sockfd==-1 )
	{
		perror("failed");
		exit(1);
	}

	/* bind the server to a socket */
	r = bind( sockfd,server->ai_addr,server->ai_addrlen);
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}
	puts("UDP server is listening...");

	/* no need to call listen() or accept() for a UDP server */

	client_size = sizeof(struct sockaddr);
	r = recvfrom(
			sockfd,
			input,
			size,
			0,
			&client,
			&client_size
			);
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}

	r = sendto(
			sockfd,
			buffer,
			strlen(buffer),
			0,
			&client,
			client_size
			);
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}

	/* clean-up */
	freeaddrinfo(server);
	close(sockfd);

	return(0);
}
