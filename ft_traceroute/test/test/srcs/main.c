# include <stdio.h>
# include <string.h>
# include <netdb.h>
# include <netinet/ip_icmp.h>

# define PACKET_SIZE    64

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
    //int fd_sock;
    int sock_out;
    char    buffer[40];
    socklen_t     len;
    int recv;
    struct sockaddr_in /*servaddr,*/ cliaddr;
    //char    packet[PACKET_SIZE];
    //struct icmphdr *icmp_header;
    //uint32_t    ip;
    //int send;
    int iphdr_size;
    size_t  i;

    // fd_sock = socket(AF_INET, SOCK_DGRAM, 0);

    // memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

	// servaddr.sin_family = AF_INET;
	// servaddr.sin_addr.s_addr = INADDR_ANY;
	// servaddr.sin_port = htons(33434);

    // bind(fd_sock, (struct sockaddr *)&(servaddr), sizeof(servaddr));

    sock_out = socket(AF_INET, SOCK_RAW, IPPROTO_ICMP);

    i = 1;

    while (1)
    {
        printf("###%ld###\n", i);
        
        recv = recvfrom(sock_out, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);

        printf("recv: %d\n", recv);

       // printf("%s\n", buffer);

        printf("version: %d\n", ((struct iphdr *)buffer)->version);
        printf("ihl: %d\n", ((struct iphdr *)buffer)->ihl);
        printf("tos: %d\n", ((struct iphdr *)buffer)->tos);
        printf("tot_len: %d\n", ntohs(((struct iphdr *)buffer)->tot_len));
        printf("id: %d\n", ntohs(((struct iphdr *)buffer)->id));
        printf("frag_off: %d\n", ((struct iphdr *)buffer)->frag_off);
        printf("ttl: %d\n", ((struct iphdr *)buffer)->ttl);
        printf("protocol: %d\n", ((struct iphdr *)buffer)->protocol);
        printf("check: %d\n", ((struct iphdr *)buffer)->check);
        printf("saddr: %d.%d.%d.%d\n", (0xff & ((struct iphdr *)buffer)->saddr), (0xff00 & ((struct iphdr *)buffer)->saddr) >> 8 , (0xff0000 & ((struct iphdr *)buffer)->saddr) >> 16, (0xff000000 & ((struct iphdr *)buffer)->saddr) >> 24);
        printf("daddr: %d.%d.%d.%d\n", (0xff & ((struct iphdr *)buffer)->daddr), (0xff00 & ((struct iphdr *)buffer)->daddr) >> 8 , (0xff0000 & ((struct iphdr *)buffer)->daddr) >> 16, (0xff000000 & ((struct iphdr *)buffer)->daddr) >> 24);
    
        iphdr_size = ((struct iphdr *)buffer)->ihl * 4;


        printf("type: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->type);
        printf("code: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->code);
        printf("checksum: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->checksum);
        printf("id: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->un.echo.id);
        printf("sequence: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->un.echo.sequence);
        printf("gateway: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->un.gateway);
        printf("__glibc_reserved: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->un.frag.__glibc_reserved);
        printf("mtu: %d\n", ((struct icmphdr *)(buffer + iphdr_size))->un.frag.mtu);



        // ip = cliaddr.sin_addr.s_addr;

        // printf("%d.%d.%d.%d\n", (0xff & ip), (0xff00 & ip) >> 8 , (0xff0000 & ip) >> 16, (0xff000000 & ip) >> 24);

        // memset(&packet, 0, sizeof(packet));
        // icmp_header = (struct icmphdr *)packet;
        // icmp_header->type = 3;
        // icmp_header->code = 3;
        // icmp_header->checksum = 0;
        // icmp_header->un.echo.sequence = 0;
        // icmp_header->un.echo.id = 0;

        // icmp_header->checksum = checksum((unsigned short *)packet, PACKET_SIZE);

        // send = sendto(sock_out, packet, PACKET_SIZE, 0, (struct sockaddr*)&cliaddr,  sizeof(struct sockaddr));

        // printf("send: %d\n", send);
        i++;
    }

    return (0);
}