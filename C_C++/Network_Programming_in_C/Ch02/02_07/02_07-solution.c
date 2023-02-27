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

	memset( &hints, 0, sizeof(struct addrinfo) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	r = getaddrinfo( 0, "8080", &hints, &server );	/* here */
	if( r!=0 )
	{
		perror("failed");
		exit(1);
	}

	sockfd = socket(server->ai_family,server->ai_socktype,server->ai_protocol);	/* here */
	if( sockfd==-1 )
	{
		perror("failed");
		exit(1);
	}

	r = bind(sockfd,server->ai_addr,server->ai_addrlen);	/* here */
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}

	r = listen(sockfd,1);	/* here */
	if( r==-1 )
	{
		perror("failed");
		exit(1);
	}

	client_len = sizeof(client_address);
	clientfd = accept(sockfd,&client_address,&client_len);	/* here */
	if( clientfd==-1 )
	{
		perror("failed");
		exit(1);
	}

	close(clientfd);
	freeaddrinfo(server);
	close(sockfd);
	return(0);
}
