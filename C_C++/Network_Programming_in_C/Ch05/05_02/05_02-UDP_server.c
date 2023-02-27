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

	/* keep accepting connections */
	while(1)
	{
		/* obtain the string from the client */
		client_size = sizeof(struct sockaddr);
		r = recvfrom(sockfd,input,size,0,&client,&client_size);
		if( r==-1 )
		{
			perror("failed");
			exit(1);
		}

		/* build the output string */
		input[r] = '\0';
		strcpy(output,"SERVER> ");
		strcat(output,input);

		/* return the string to the client */
		r = sendto(sockfd,output,strlen(output),0,&client,client_size);
		if( r==-1 )
		{
			perror("failed");
			exit(1);
		}
	}	/* end while */

	/* clean-up and close */
	freeaddrinfo(server);
	close(sockfd);

	return(0);
}
