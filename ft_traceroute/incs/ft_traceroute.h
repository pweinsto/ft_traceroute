#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <arpa/inet.h>
# include <netinet/in.h>
# include <netinet/ip.h>
# include <netinet/ip_icmp.h>
# include <netinet/udp.h>
# include <netdb.h>
# include <sys/time.h>

# include "../libs/libft/libft.h"
# include "error.h"

# define PORT   33434
# define MAXHOP 64
# define DATA   "SUPERMAN"
# define WAIT   3000 //in microseconds

typedef struct s_probe
{
    size_t  id;
    //timeval time;
}   t_probe;

typedef struct s_hop
{
    size_t  ttl;
    struct t_probe *probe[3];
    size_t  last_ip;
}   t_hop;

typedef struct s_trace
{
    char            *domain;
    char            *ip;
    struct addrinfo *info;
    int             ttl;
    int             out_socket;
    int             in_socket;
    struct sockaddr_in  dest;
    int             valid_probe;
}   t_trace;

struct addrinfo *dns_lookup(t_trace  *trace, char *host);
void error(const char *error);
float	time_diff(struct timeval init_time);

int parser(char **argv, t_trace  *trace);

int set_out_socket(t_trace *trace);
int set_in_socket(t_trace *trace);

#endif