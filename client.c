#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (3 != argc)
    {
        printf("Usage:%s hostname portnumber\n", argv[0]);
        return EXIT_FAILURE;
    }

    // put your code here

    /* create socket */
    int     sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (-1 == sockfd)
    {
        printf("create socket:: %s\n", strerror(errno));
        return -1;
    }

    /* set server address */
    int                 server_port = atoi(argv[2]);
    struct sockaddr_in  server_addr;

    server_addr.sin_family  = AF_INET;
    server_addr.sin_port    = htons(server_port);
    if(1 != inet_pton(AF_INET, argv[1], &server_addr.sin_addr))
    {
        printf("set server addr:: setting address to [%s] failed\n", argv[1]);
        return -1;
    }

    /* communication with server */
    int     len;
    int     size;
    char    buf[BUFFER_SIZE];

    while(1)
    {
        scanf("%s", buf);
        printf("client send::%s\n", buf);
        /* 添加换行符，防止服务器无法立刻响应消息 */
        len = strlen(buf);
        // buf[len++] = '\n';
        size = sendto(sockfd, buf, len, 0, (struct sockaddr *)&server_addr, sizeof server_addr);
        // printf("client send(%d)::%s\n", size, buf);
        
    }


    return EXIT_SUCCESS;
}
