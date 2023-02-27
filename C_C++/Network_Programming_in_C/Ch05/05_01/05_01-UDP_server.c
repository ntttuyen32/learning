#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

/* UDP server returns the passed string */
int main()
{
	struct addrinfo hints,*server;
	struct sockaddr client;
	socklen_t client_size;
	int r,sockfd;
	const int size = 1024;
	char input[size],output[size];

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

	/* obtain client input */
	client_size = sizeof(struct sockaddr);
	r = recvfrom(sockfd,input,size,0,&client,&client_size);
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}

	/* get the client name */
	getnameinfo(&client,client_size,output,size,0,0,NI_NUMERICHOST);

	/* send back their IP address */
	sendto(sockfd,output,strlen(output),0,&client,client_size);

	/* clean-up and close */
	freeaddrinfo(server);
	close(sockfd);

	return(0);
}
