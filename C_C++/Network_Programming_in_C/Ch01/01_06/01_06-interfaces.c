#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>

int main()
{
	struct ifaddrs *adapters,*a;
	int r,addrfam;
	const int ap_size = 100;
	char ap[ap_size];

	puts("This computer's network interfaces:");
	r = getifaddrs(&adapters);
	if ( r==-1)
	{
		perror("Interfaces");
		exit(1);
	}
	printf("%-8s%-8s%s\n","Name","Family","Address");

	/* walk through the linked list */
	a = adapters;
	while(a)
	{
		addrfam = a->ifa_addr->sa_family;
		if( addrfam==AF_INET || addrfam==AF_INET6)
		{
			getnameinfo(a->ifa_addr,
					addrfam==AF_INET ?
					sizeof(struct sockaddr_in)
					: sizeof(struct sockaddr_in6),
					ap,
					ap_size,
					0,
					0,
					NI_NUMERICHOST);
			printf("%-8s%-8s%s\n",
					a->ifa_name,
					addrfam==AF_INET ? "IPv4" : "IPv6",
					ap
				  );
		}
		a = a->ifa_next;
	}

	/* free memory - linked list */
	freeifaddrs(adapters);
	return(0);
}
