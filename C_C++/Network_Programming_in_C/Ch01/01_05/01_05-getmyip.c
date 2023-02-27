#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
	/* server information */
    const char *google_dns_server = "8.8.8.8";
    const char *dns_port = "53";
	const char *p;
	char buffer[BUFSIZ];
	int sockfd,r;
	struct addrinfo hints,*peer_address;
	struct sockaddr_in name;
    socklen_t namelen;
    
	/* cnofigure the peer_address addrinfo structure */
	memset( &hints, 0, sizeof(struct addrinfo) );
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	r = getaddrinfo(google_dns_server,dns_port, &hints, &peer_address );
	if( r!=0 )
	{
		perror("failed");
		exit(1);
	}

	/* connect the socket */
	sockfd = socket(
			peer_address->ai_family,
			peer_address->ai_socktype,
			peer_address->ai_protocol
			);
    if(sockfd==-1)
    {
		perror("failed");
		exit(1);
	}
    
	/* connect to the server */
	r = connect( sockfd, peer_address->ai_addr, peer_address->ai_addrlen );
	if( r==-1)
	{
		perror("failed");
		exit(1);
	}
    
	/* obtain the local socket's name/address */
    namelen = sizeof(name);
    r = getsockname(sockfd, (struct sockaddr*) &name, &namelen);
	if( r==-1)
	{
		perror("failed");
		exit(1);
	}
    	
	/* output the results */
    p = inet_ntop(peer_address->ai_family, &name.sin_addr, buffer, BUFSIZ);
	if(p != NULL)
	{
		printf("Local IP is: %s\n",buffer);
	}
	else
	{
		fprintf(stderr,"Operation failed\n");
	}

	/* done, close the socket */
    close(sockfd);
    return(0);
}
