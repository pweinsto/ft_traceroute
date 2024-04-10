#ifndef FT_TRACEROUTE_H
# define FT_TRACEROUTE_H

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
# include <netdb.h>
# include <sys/time.h>

# include "../libs/libft/libft.h"

# define PORT   33434
# define MAXHOP 3
# define DATA   "SUPERMAN"


// typedef struct s_probe
// {
//     size_t  id:
//     //timeval time;
// }   t_probe;

// typedef struct s_hop
// {
//     size_t  ttl;
//     struct t_probe probe[3];

// }   t_hop;

struct addrinfo *dns_lookup(char *host);

# endif