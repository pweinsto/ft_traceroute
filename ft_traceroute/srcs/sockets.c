# include "../incs/ft_traceroute.h"

int set_out_socket(t_trace *trace)
{
    int t;

    t = 1;

    if ((trace->out_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        freeaddrinfo(trace->info);
        free(trace);
        error(strerror(errno));
    }

    if ((setsockopt(trace->out_socket, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t))) == -1)
    {
        close(trace->out_socket);
        freeaddrinfo(trace->info);
        free(trace);
        error(strerror(errno));
    }

    ft_bzero(&trace->dest, sizeof(trace->dest));

    trace->dest.sin_family = AF_INET;
	trace->dest.sin_port = htons(PORT);
	trace->dest.sin_addr = ((struct sockaddr_in *)(trace->info->ai_addr))->sin_addr;

    return (1);
}

int set_in_socket(t_trace *trace)
{
    struct sockaddr_in  saddr;
    int t;

    t = 1;
    
    ft_bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if ((trace->in_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)) == -1)
    {
        close(trace->out_socket);
        freeaddrinfo(trace->info);
        free(trace);
        error(strerror(errno));
    }

    if ((bind(trace->in_socket, (struct sockaddr *)&(saddr), sizeof(saddr))) == -1)
    {
        close(trace->out_socket);
        close(trace->in_socket);
        freeaddrinfo(trace->info);
        free(trace);
        error(strerror(errno));
    }

    if ((setsockopt(trace->in_socket, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t))) == -1)
    {
        close(trace->out_socket);
        close(trace->in_socket);
        freeaddrinfo(trace->info);
        free(trace);
        error(strerror(errno));
    }

    return (1);
}