#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>

int main()
{
	const char *server = "127.0.0.1";	/* change to server's address */
	struct addrinfo hints,*host;
	int r,sockfd;
	const int size = 1024;
	char buffer[size];

	/* configure the remote address */
	memset( &hints, 0, sizeof(hints) );	/* use memset_s() */
	hints.ai_family = AF_INET;			/* IPv4 */
	hints.ai_socktype = SOCK_DGRAM;		/* UDP connection */
	r = getaddrinfo( server, "8080", &hints, &host );
	if( r!=0 )
	{
		perror("failed");
		exit(1);
	}

	/* create the socket */
	sockfd = socket(host->ai_family,host->ai_socktype,host->ai_protocol);
	if( sockfd==-1 )
	{
		perror("failed");
		exit(1);
	}

	/* send something to the server */
	r = sendto( sockfd,"\n",1,0,host->ai_addr,host->ai_addrlen);

	r = recvfrom(sockfd,buffer,size,0,host->ai_addr,&host->ai_addrlen);
	buffer[r] = '\0';
	printf("%s\n",buffer);

	/* all done, clean-up */
	freeaddrinfo(host);
	close(sockfd);

	return(0);
}
