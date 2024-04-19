# include <stdio.h>
# include <string.h>
# include <netdb.h>
# include <netinet/ip_icmp.h>

# define PACKET_SIZE    45

unsigned short	checksum(unsigned short *data, int len)
{
	unsigned long	checksum;

	checksum = 0;
	while (len > 1)
	{
		checksum = checksum + *data++;
		len = len - sizeof(unsigned short);
	}
	if (len)
		checksum = checksum + *(unsigned char*)data;
	checksum = (checksum >> 16) + (checksum & 0xffff);
	checksum = checksum + (checksum >> 16);
	return (unsigned short)(~checksum);
}

int main(void)
{
    int fd_sock;
    int sock_out;
    char    buffer[40];
    socklen_t     len;
    int recv;
    struct sockaddr_in servaddr, cliaddr;
    char    packet[PACKET_SIZE];
    struct icmphdr *icmp_header;
    uint32_t    ip;
    int send;
    size_t  i;
    int val;

    fd_sock = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(33434);

    bind(fd_sock, (struct sockaddr *)&(servaddr), sizeof(servaddr));

    sock_out = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    val = IP_PMTUDISC_DONT;
    setsockopt(sock_out, SOL_IP, IP_MTU_DISCOVER, &val, sizeof(val));
    
    i = 1;

    while (1)
    {
        printf("###%ld###\n", i);
        
        recv = recvfrom(fd_sock, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);

        printf("recv: %d\n", recv);

        printf("%s\n", buffer);

        ip = cliaddr.sin_addr.s_addr;

        printf("%d.%d.%d.%d\n", (0xff & ip), (0xff00 & ip) >> 8 , (0xff0000 & ip) >> 16, (0xff000000 & ip) >> 24);

        memset(&packet, 0, sizeof(packet));
        icmp_header = (struct icmphdr *)packet;
        icmp_header->type = 3;
        icmp_header->code = 3;
        icmp_header->checksum = 0;
        icmp_header->un.echo.sequence = 0;
        icmp_header->un.echo.id = 0;

        icmp_header->checksum = checksum((unsigned short *)packet, PACKET_SIZE);

        printf("icmp_checksum: %d\n", icmp_header->checksum);

        send = sendto(sock_out, packet, PACKET_SIZE, 0, (struct sockaddr*)&cliaddr,  sizeof(struct sockaddr));

        printf("send: %d\n", send);

        i++;
    }

    return (0);
}