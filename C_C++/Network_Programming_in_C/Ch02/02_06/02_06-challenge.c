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
	getaddrinfo( 0, "8080", &hints, &server );	/* here */

	socket(server->ai_family,server->ai_socktype,server->ai_protocol);	/* here */
	bind(sockfd,server->ai_addr,server->ai_addrlen);	/* here */
	listen(sockfd,1);	/* here */
	client_len = sizeof(client_address);
	accept(sockfd,&client_address,&client_len);	/* here */

	close(clientfd);
	freeaddrinfo(server);
	close(sockfd);
	return(0);
}
