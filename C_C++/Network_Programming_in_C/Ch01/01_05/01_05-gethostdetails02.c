#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>

int main()
{
	char host[BUFSIZ];
	int r;
	struct hostent *hostdata;
	char **addresses;

	/* check this machine */
	r = gethostname(host,BUFSIZ);
	if( r==-1 )
	{
		fprintf(stderr,"Unable to obtain host name\n");
		exit(1);
	}
	
	/* report the host name */
	printf("This host is named '%s'\n",host);
	
	/* get information about the host */
	hostdata = gethostbyname(host);		/* function is obsolete */
	if( hostdata==NULL )
	{
		fprintf(stderr,"Can't obtain host data\n");
		exit(1);
	}
	printf("Address(es): ");
	addresses = hostdata->h_addr_list;
	while( *addresses )
	{
		printf("%s\n", inet_ntoa(*(struct in_addr *)*addresses));
		addresses++;
	}

	return(0);
}
