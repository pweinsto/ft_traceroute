# include "../incs/ft_traceroute.h"

int main(int argc, char **argv)
{
    int     sockfd;
    struct  sockaddr_in dest;
    struct addrinfo *info;
    char    *ip;
    void    *buffer[IP_MAXPACKET];
    struct sockaddr  source;
    unsigned int     len;
    int     recv;
    int     send;
    char *hello = "hello world!";


    (void)argc;

    info = dns_lookup(argv[1]);

    ip = ft_calloc(INET_ADDRSTRLEN, 1);
    inet_ntop(AF_INET, &info->ai_addr->sa_data[2], ip, INET_ADDRSTRLEN);
    printf("%s\n", ip);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    memset(&dest, 0, sizeof(dest));

    dest.sin_family = AF_INET;
	dest.sin_port = htons(PORT);
	dest.sin_addr = ((struct sockaddr_in *)(info->ai_addr))->sin_addr;


    if ((send = sendto(sockfd, hello, ft_strlen(hello), 0, (const struct sockaddr *) &dest, sizeof(dest))) == -1)
        printf("send: fail!\n");
    else
        printf("send: %d\n", send);

    recv = recvfrom(sockfd, buffer, sizeof(buffer), MSG_WAITALL, &source, &len);

    printf("recv: %d\n", recv);

    return (0);
}