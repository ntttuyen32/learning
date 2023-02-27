#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>

int main()
{
	struct addrinfo hints,*server;
	int r,sockfd,clientfd;
	struct sockaddr client_address;
	socklen_t client_len;
	const int buffer_size = 1024;
	char buffer[buffer_size];

	/* configure the server to use the localhost, port 8080, TCP */
	printf("Configuring server...");
	memset( &hints, 0, sizeof(struct addrinfo) );	/* use memset_s() */
	hints.ai_family = AF_INET;			/* IPv4 connection */
	hints.ai_socktype = SOCK_STREAM;	/* TCP, streaming */
	r = getaddrinfo( 0, "8080", &hints, &server );
	if( r!= 0 )
	{
		perror("failed");
		exit(1);
	}
	puts("done");

	/* create the socket to use for communications */
	printf("Assign a socket...");
	sockfd = socket(
			server->ai_family,		/* domain, TCP/UDP */
			server->ai_socktype,	/* type, stream or datagram */
			server->ai_protocol		/* protocol */
			);
	if( sockfd==-1 )
	{
		perror("failed");
		exit(1);
	}
	puts("done");

	/* bind the server to a socket */
	printf("Binding socket...");
	r = bind(sockfd,server->ai_addr,server->ai_addrlen);
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}
	puts("done");

	/* listen for incoming connections */
	printf("Listening...");
	r = listen(sockfd,1);
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}
	puts("done");

	/* accept a new connection */
	printf("Accepting new connection ");
	client_len = sizeof(client_address);
	clientfd = accept(sockfd,&client_address,&client_len);
	if( clientfd==-1 )
	{
		perror("failed");
		exit(1);
	}
	printf("on file descriptor %d\n",clientfd);

	/* client is now connected */
	r = recv(clientfd,buffer,buffer_size,0);
	if( r>0 )
	{
		printf("Received %d bytes:\n---\n",r);
		for(int x=0; x<r; x++)
			putchar(buffer[x]);
	}

	/* close the client socket */
	close(clientfd);

	/* free allocated memory */
	freeaddrinfo(server);
	/* close the socket */
	close(sockfd);
	puts("Socket closed, done");
	return(0);
}
