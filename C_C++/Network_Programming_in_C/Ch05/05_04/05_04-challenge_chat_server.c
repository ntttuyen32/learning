#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <sys/select.h>

#define TRUE 1
#define FALSE 0

int main()
{
	/* define variables here */

	/* setup the server */
	getaddrinfo();

	/* create a socket */
	socket();

	/* bind to a port */
	bind();

	/* listen for a connection*/
	puts("Chat Server is listening...");
	listen();

	/* deal with multiple connections */
								/* maximum connections */
								/* initialize file descriptor set */
								/* set the server's file descriptor */
	/* endless loop to process the connections */
	while()
	{
		/* backup the main file descriptor set into a read set for processing */
		
		/* scan the connections for any activity */
		select();

		/* loop to check for active connections */
		for()
		{
			/* filter only active or new clients */
			if()
			{
				/* check the server for a new connection */
				if()
				{
					/* add the new client */
					accept();

					/* connection accepted, get IP address */
					getnameinfo();
					/* update array of IP addresses */

					/* add new client socket to the file descriptor list */

					/* welcome the new user: create welcome string and send */
					/* welcome string: "SERVER> Welcome xxx.xxx.xxx.xxx to the chat server\n"
					   "Type 'close' to disconnect; 'shtudown' to stop\n" */

					send();

					/* tell everyone else about the new user */
					/* build the string: "SERVER> xxx.xxx.xxx.xxx has joined the server" */

					/* loop from the server's file descriptor up,
					   sending the string to each active connection */
					for()
					{
						if()
							send();
					}
					/* output the string to the local console as well */
					printf();
					
				} /* end if to add new client */
				/* deal with incoming data from an established connection */
				else
				{
					/* check input buffer for the current fd */
					recv();
					/* if nothing received, disconnect them */
					if()
					{
													/* clear the file descriptor */
													/* close the file descriptor/socket */
						
						/* tell others that the user has disconnected */
						/* build the string: "SERVER> xxx.xxx.xxx.xxx, disconnected" */
						
						/* loop through all connections (not the server) to send the string */
						for()
						{
							if()
							{
								send();
							}
						}
						/* output the string locally */
						printf();
					}
					/* at this point, the connected client has text to share */
					/* share the incoming text with all connections */
					else
					{
													/* cap the received string */
						/* first check to see whether the "shutdown\n" string was sent */
						if()
						{
											/* if so, set the loop's terminating condition */
						}
						/* otherwise, echo the received string to all connected fds */
						else
						{
							/* build the string: "xxx.xxx.xxx.xxx> [text]" */
							
							/* loop through all connections, but not the server */
							for()
							{
								/* check for an active file descriptor */
								if()
								{
									/* send the built string */
									send();
								}
							}
							/* echo the string to the server as well */
							printf();
						}	/* end else for connected client */
					}	/* end else after disconnect */
				} /* end else to send/recv from client(s) */
			} /* end if */
		} /* end for loop through connections */
	} /* end while */

	/* generate local message: "SERVER> Shutdown issued; cleaning up" */
	puts("SERVER> Shutdown issued; cleaning up");
	/* close the socket and free any allocated memory */
	close();
	freeaddrinfo();
	return(0);
}
