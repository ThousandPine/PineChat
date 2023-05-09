#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define BACKLOG 10
#define BUFFER_SIZE 1024

int main(int argc, char *argv[])
{
    if (2 != argc)
    {
        printf("Usage:%s portnumber\n", argv[0]);
        return EXIT_FAILURE;
    }

    // put your code here

    /* create socket */
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (-1 == sockfd)
    {
        printf("create socket:: %s\n", strerror(errno));
        return -1;
    }

    /* bind socket */
    int                 listen_port = atoi(argv[1]);
    struct sockaddr_in  server_addr;

    server_addr.sin_family      = AF_INET;
    server_addr.sin_port        = htons(listen_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == bind(sockfd, (struct sockaddr *)&server_addr, sizeof server_addr))
    {
        printf("bind socket::%s\n", strerror(errno));
        return -1;
    }

    /* communication with client */
    int                 size = 1;
    char                buf[BUFFER_SIZE];
    struct sockaddr_in  client_addr;
    socklen_t           client_addr_len = sizeof client_addr;

    while(1)
    {
        /* receive client msg */
        size = recvfrom(sockfd, buf, sizeof buf, 0, (struct sockaddr *)&client_addr, &client_addr_len);

        buf[size] = '\0';
        printf("server receive(%d)::%s\n", size, buf); 
        // fflush(stdout); /* 若不刷新缓冲区，printf就只会立即输出\n之前的内容，在结尾没有\n的情况下就会出现内容输出不全或无法输出，这其中也有循环开头recv阻塞的原因 */
        sendto(sockfd, buf, size, 0, (struct sockaddr *)&client_addr, client_addr_len);
    }

    return EXIT_SUCCESS;
}
