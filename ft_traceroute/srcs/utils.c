# include "../incs/ft_traceroute.h"

struct addrinfo *dns_lookup(char *host)
{
    struct addrinfo hints;
    struct addrinfo *res;

    ft_bzero(&hints, sizeof(hints));

    hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_CANONNAME;

	if (getaddrinfo(host, NULL, &hints, &res))
       printf("unknown host\n");
    return res;
}