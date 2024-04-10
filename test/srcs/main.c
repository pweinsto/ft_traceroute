# include <stdio.h>
# include <string.h>
# include <netdb.h>

int main(void)
{
    int fd_sock;
    char    buffer[40];
    socklen_t     len;
    int recv;
    struct sockaddr_in servaddr, cliaddr;

    fd_sock = socket(AF_INET, SOCK_DGRAM, 0);

    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(33434);

    bind(fd_sock, (struct sockaddr *)&(servaddr), sizeof(servaddr));

    recv = recvfrom(fd_sock, buffer, sizeof(buffer), MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);

    printf("recv: %d\n", recv);

    printf("%s\n", buffer);

    return (0);
}