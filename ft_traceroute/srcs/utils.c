# include "../incs/ft_traceroute.h"

struct addrinfo *dns_lookup(char *host)
{
    struct addrinfo hints;
    struct addrinfo *res;

    ft_bzero(&hints, sizeof(hints));
	if (getaddrinfo(host, NULL, &hints, &res))
       printf("unknown host\n");
    return res;
}