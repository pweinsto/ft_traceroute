# include "../incs/ft_traceroute.h"

int main(int argc, char **argv)
{
  
    char                buffer[IP_MAXPACKET];
    struct sockaddr_in  source;
    socklen_t           len;
    int                 recv;
    int                 send;
    char                data[] = DATA;
    t_trace             *trace;
    size_t              probe;
    float               timediff;
    struct timeval      init_time;
    uint32_t            prev_ip;
    struct iphdr        *ip;
    struct icmphdr      *icmp;   



    if (argc <= 1)
        error(NO_ARG);

    if (!(trace = ft_calloc(sizeof(t_trace), 1)))
        error(strerror(errno));

    parser(argv, trace);

    set_out_socket(trace);
    set_in_socket(trace);

    ft_bzero(&source, sizeof(source));
    len = sizeof(source);

    dprintf(STDOUT_FILENO, "ft_traceroute to %s (%s), %d hops max", trace->domain, trace->ip, MAXHOP);

    trace->ttl = 1;
    while (trace->ttl < MAXHOP)
    {
        dprintf(STDOUT_FILENO, "\n");

        if ((setsockopt(trace->out_socket, SOL_IP, IP_TTL, &trace->ttl, sizeof(trace->ttl))) == -1)
        {
            freeaddrinfo(trace->info);
            free(trace);
            error(strerror(errno));
        }

        probe = 0;
        prev_ip = 0;
        while (probe < 3)
        {
            if ((send = sendto(trace->out_socket, data, sizeof(data), 0, (const struct sockaddr *) &trace->dest, sizeof(trace->dest))) == -1)
            {
                freeaddrinfo(trace->info);
                free(trace);
                error(strerror(errno));
            }

            if (gettimeofday(&init_time, NULL) == -1)
            {
                freeaddrinfo(trace->info);
                free(trace);
                error(strerror(errno));
            }

            ft_bzero(buffer, IP_MAXPACKET);

            while ((timediff = time_diff(init_time)) <= WAIT)
            {
                recv = recvfrom(trace->in_socket, buffer, sizeof(buffer), MSG_DONTWAIT, (struct sockaddr *)&source, &len);

                if (recv > 0)
                {
                    ip = (struct iphdr *)buffer;
                    icmp = (struct icmphdr *)(buffer + (ip->ihl * 4));

                    if (icmp->type != ICMP_TIME_EXCEEDED && icmp->type != ICMP_DEST_UNREACH)
                        continue;
                    
                    break;
                }
            }
            if (probe == 0 )
                dprintf(STDOUT_FILENO, " %2d  ", trace->ttl);

            if (timediff > WAIT)
                dprintf(STDOUT_FILENO, " * ");
            else
                {
                    if (ip->saddr != prev_ip)
                    {
                        dprintf(STDOUT_FILENO, " %d.%d.%d.%d ", (0xff & ip->saddr), (0xff00 & ip->saddr) >> 8 , (0xff0000 & ip->saddr) >> 16, (0xff000000 & ip->saddr) >> 24);
                        prev_ip = ip->saddr;
                    }

                    dprintf(STDOUT_FILENO, " %.3fms ", timediff);

                    if (icmp->type == ICMP_DEST_UNREACH && icmp->code == ICMP_HOST_ANO)
                        dprintf(STDOUT_FILENO, "!* ");
                }

            probe++;
        }

        if (icmp->type == ICMP_DEST_UNREACH)
        {
            dprintf(STDOUT_FILENO, "\n");
            freeaddrinfo(trace->info);
            free(trace);
            exit(0);
        }     
        trace->ttl++;
    }

    return (0);
}