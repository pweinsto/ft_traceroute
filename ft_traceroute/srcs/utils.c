# include "../incs/ft_traceroute.h"

struct addrinfo *dns_lookup(t_trace  *trace, char *host)
{
    struct addrinfo hints;
    struct addrinfo *res;

    ft_bzero(&hints, sizeof(hints));

    hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_DGRAM;
	hints.ai_protocol = IPPROTO_UDP;
	hints.ai_flags = AI_CANONNAME;

	if (getaddrinfo(host, NULL, &hints, &res))
    {
        free(trace);
        error(UNK_HOST);
    }
 
    return res;
}

void error(const char *error)
{
    fprintf(stderr, error);
	fprintf(stderr, "\n");
    exit(EXIT_FAILURE);
}

float	time_diff(struct timeval init_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);

	return (current_time.tv_sec - init_time.tv_sec) * 1000 + (current_time.tv_usec - init_time.tv_usec) / 1000.0;
}
