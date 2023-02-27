#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>

int main()
{
	int r,sockfd;
	struct addrinfo hints,*host;
	const char *hello = "Howdy, TCP Server!\n";
	const int buffer_size = 1024;
	char buffer[buffer_size];

	memset(&hints, 0, sizeof(struct addrinfo));		/* memset_s() */
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	r = getaddrinfo( "127.0.0.1", "8080", &hints, &host);
	if( r!=0 )
	{
		perror("TCP client");
		exit(1);
	}

	/* create a socket */
	sockfd = socket(host->ai_family,host->ai_socktype,host->ai_protocol);
	if( sockfd==-1 )
	{
		perror("TCP client");
		exit(1);
	}

	/* connect and get the info */
	r = connect( sockfd, host->ai_addr, host->ai_addrlen);
	if( r == -1)
	{
		perror("TCP client");
		exit(1);
	}

	/* send something to say hello */
	r = send(sockfd, hello, strlen(hello), 0 );
	if( r==-1 )
	{
		perror("TCP client");
		exit(1);
	}

	r = recv(sockfd, buffer, buffer_size, 0);
	buffer[r] = '\0';
	printf("%s\n",buffer);

	freeaddrinfo(host);
	close(sockfd);

	return(0);
}
