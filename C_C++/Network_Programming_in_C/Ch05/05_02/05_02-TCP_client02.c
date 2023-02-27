#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <unistd.h>
#include <sys/socket.h>

int main()
{
	int r,sockfd,x;
	struct addrinfo hints,*host;
	const int buffer_size = 1024;
	char buffer[buffer_size];

	memset(&hints, 0, sizeof(struct addrinfo));		/* memset_s() */
	hints.ai_family = AF_INET;			/* IPv4 connection */
	hints.ai_socktype = SOCK_STREAM;	/* TCP, streaming */
	r = getaddrinfo( 0, "8080", &hints, &host);
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
	r = connect(sockfd,host->ai_addr,host->ai_addrlen);
	if( r == -1)
	{
		perror("TCP client");
		exit(1);
	}

	while(1)
	{
		/* gather input string */
		printf("Type something: ");
		fgets(buffer,buffer_size,stdin);
		/* quit on zero input */
		if( buffer[0]=='\n' )
			break;
		/* otherwise, remove the newline */
		for( x=0; x<buffer_size; x++ )
		{
			if( buffer[x]=='\n' )
			{
				buffer[x] = '\0';
				break;
			}
		}

		/* send the input string */
		r = send(sockfd, buffer, strlen(buffer), 0 );
		if( r==-1 )
		{
			perror("TCP client");
			exit(1);
		}

		r = recv(sockfd, buffer, buffer_size, 0);
		buffer[r] = '\0';
		printf("%s\n",buffer);
	} /* end while */

	/* close-up */
	freeaddrinfo(host);
	close(sockfd);

	return(0);
}
