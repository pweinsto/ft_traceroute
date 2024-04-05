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
    //char *hello = "hello world!";
    int     t = 1;
    int     ttl = 2;
    char    packet[64];
    struct icmphdr *icmp_header;
    size_t  iphdr_size;

    (void)argc;

    info = dns_lookup(argv[1]);

    ip = ft_calloc(INET_ADDRSTRLEN, 1);
    inet_ntop(AF_INET, &info->ai_addr->sa_data[2], ip, INET_ADDRSTRLEN);
    printf("%s\n", ip);

    fd_out = socket(AF_INET, SOCK_DGRAM, 0);
    setsockopt (fd_out, SOL_IP, IP_TTL, &ttl, sizeof(ttl));
    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	dest.sin_addr = ((struct sockaddr_in *)(info->ai_addr))->sin_addr;

    icmp_header = (struct icmphdr *)packet;
    icmp_header->type = ICMP_ECHO;
    icmp_header->code = 0;
    icmp_header->checksum = 0;
    icmp_header->un.echo.sequence = htons(0);
    icmp_header->un.echo.id = getpid();

    if ((send = sendto(fd_out, icmp_header, 64, 0, (const struct sockaddr *) &dest, sizeof(dest))) == -1)
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

    iphdr_size = ((struct iphdr *)buffer)->ihl * 4;

    printf("type: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->type);
    printf("code: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->code);

    return (0);
}