# include "../incs/ft_traceroute.h"

int main(int argc, char **argv)
{
    int     fd_out;
    int     fd_in;
    struct  sockaddr_in dest;
    struct addrinfo *info;
    char    *ip;
    char    buffer[IP_MAXPACKET];
    struct sockaddr  source;
    socklen_t     len;
    int     recv;
    int     send;
    int     t = 1;
    int     ttl = 6;
    size_t  iphdr_size;
    struct sockaddr_in	saddr;
    char    data[] = DATA;


    (void)argc;

    info = dns_lookup(argv[1]);

    ip = ft_calloc(INET_ADDRSTRLEN, 1);
    inet_ntop(AF_INET, &info->ai_addr->sa_data[2], ip, INET_ADDRSTRLEN);
    printf("%s\n", ip);

    ft_bzero(&saddr, sizeof(saddr));
	saddr.sin_family = AF_INET;
	saddr.sin_addr.s_addr = INADDR_ANY;
	saddr.sin_port = htons(0);

    fd_out = socket(AF_INET, SOCK_DGRAM, 0);

    bind(fd_out, (struct sockaddr *)&(saddr), sizeof(saddr));

    setsockopt(fd_out, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t));
    setsockopt (fd_out, SOL_IP, IP_TTL, &ttl, sizeof(ttl));
    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	dest.sin_addr = ((struct sockaddr_in *)(info->ai_addr))->sin_addr;

    if ((send = sendto(fd_out, data, sizeof(data), 0, (const struct sockaddr *) &dest, sizeof(dest))) == -1)
        printf("send: fail!\n");
    else
        printf("send: %d\n", send);
    
    fd_in = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    setsockopt(fd_in, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t));
    
    ft_bzero(buffer, IP_MAXPACKET);

    while ((recv = recvfrom(fd_in, buffer, sizeof(buffer), MSG_DONTWAIT, &source, &len)) < 0)
    {
        printf("beeb\n");
        sleep(1);
    }

    printf("recv: %d\n", recv);
    //printf("buffer: %s\n", (char *)buffer);

    printf("version: %d\n", ((struct iphdr *)buffer)->version);
    printf("ihl: %d\n", ((struct iphdr *)buffer)->ihl);
    printf("tos: %d\n", ((struct iphdr *)buffer)->tos);
    printf("tot_len: %d\n", ntohs(((struct iphdr *)buffer)->tot_len));
    printf("id: %d\n", ((struct iphdr *)buffer)->id);
    printf("frag_off: %d\n", ((struct iphdr *)buffer)->frag_off);
    printf("ttl: %d\n", ((struct iphdr *)buffer)->ttl);
    printf("protocol: %d\n", ((struct iphdr *)buffer)->protocol);
    printf("check: %d\n", ((struct iphdr *)buffer)->check);
    printf("saddr: %d.%d.%d.%d\n", (0xff & ((struct iphdr *)buffer)->saddr), (0xff00 & ((struct iphdr *)buffer)->saddr) >> 8 , (0xff0000 & ((struct iphdr *)buffer)->saddr) >> 16, (0xff000000 & ((struct iphdr *)buffer)->saddr) >> 24);
    printf("daddr: %d.%d.%d.%d\n", (0xff & ((struct iphdr *)buffer)->daddr), (0xff00 & ((struct iphdr *)buffer)->daddr) >> 8 , (0xff0000 & ((struct iphdr *)buffer)->daddr) >> 16, (0xff000000 & ((struct iphdr *)buffer)->daddr) >> 24);
    
    iphdr_size = ((struct iphdr *)buffer)->ihl * 4;


    printf("type: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->type);
    printf("code: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->code);


    return (0);
}