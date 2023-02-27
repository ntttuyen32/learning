#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	char host[BUFSIZ];
	int r;

	/* check this machine */
	r = gethostname(host,BUFSIZ);
	if( r==-1 )
	{
		fprintf(stderr,"Unable to obtain host name\n");
		exit(1);
	}
	
	/* report the host name */
	printf("This host is named '%s'\n",host);

	return(0);
}
