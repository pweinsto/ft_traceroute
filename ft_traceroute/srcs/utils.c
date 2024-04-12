# include "../incs/ft_traceroute.h"

struct addrinfo *dns_lookup(char *host)
{
    struct addrinfo hints;
    struct addrinfo *res;

    if (!(res = ft_calloc(sizeof(struct addrinfo), 1)))
		error(strerror(errno));
    ft_bzero(&hints, sizeof(hints));

    hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_CANONNAME;

	if (getaddrinfo(host, NULL, &hints, &res))
        error(UNK_HOST);
    return res;
}

void error(const char *error)
{
    fprintf(stderr, error);
	fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}