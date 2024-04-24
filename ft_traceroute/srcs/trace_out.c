# include "../incs/ft_traceroute.h"

int set_out_socket(t_trace *trace)
{
    struct  sockaddr_in	saddr;
    int t;

    t = 1;

    ft_bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(0);

    trace->out_socket = socket(AF_INET, SOCK_DGRAM, 0);

    bind(trace->out_socket, (struct sockaddr *)&(saddr), sizeof(saddr));

    setsockopt(trace->out_socket, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t));

    memset(&trace->dest, 0, sizeof(trace->dest));

    trace->dest.sin_family = AF_INET;
	trace->dest.sin_port = htons(PORT);
	trace->dest.sin_addr = ((struct sockaddr_in *)(trace->info->ai_addr))->sin_addr;

    return (1);
}

int set_in_socket(t_trace *trace)
{
    int t;

    t = 1;
    
    trace->in_socket = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    setsockopt(trace->in_socket, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t));

    return (1);
}

// int check_packet(t_trace *trace)
// {



//     trace->valid_probe++
// }
