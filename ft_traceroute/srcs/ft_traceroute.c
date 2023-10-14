# include "../incs/ft_traceroute.h"

int main(int argc, char **argv)
{
    int     fd_out;
    int     fd_in;
    struct  sockaddr_in dest;
    struct addrinfo *info;
    char    *ip;
    void    *buffer[IP_MAXPACKET];
    struct sockaddr  source;
    unsigned int     len;
    int     recv;
    int     send;
    char *hello = "hello world!";
    int     t = 1;
    int     ttl = 4;


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


    if ((send = sendto(fd_out, hello, ft_strlen(hello), 0, (const struct sockaddr *) &dest, sizeof(dest))) == -1)
        printf("send: fail!\n");
    else
        printf("send: %d\n", send);

    fd_in = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);
    setsockopt(fd_in, SOL_SOCKET, SO_REUSEPORT, &t, sizeof(t));
    
    while ((recv = recvfrom(fd_in, buffer, sizeof(buffer), MSG_DONTWAIT, &source, &len)) < 0);

    printf("recv: %d\n", recv);
    printf("buffer: %s\n", (char *)buffer);

    return (0);
}