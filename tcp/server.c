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
    // int server_fd = socket(AF_INET, SOCK_DGRAM, 0);
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == server_fd)
    {
        printf("create socket:: %s\n", strerror(errno));
        return -1;
    }

    /* bind socket */
    int listen_port = atoi(argv[1]);
    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(listen_port);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(-1 == bind(server_fd, (struct sockaddr *)&server_addr, sizeof server_addr))
    {
        printf("bind socket::%s\n", strerror(errno));
        return -1;
    }

    /* listen socket */
    if(-1 == listen(server_fd, BACKLOG))
    {
        printf("listen socket::%s\n", strerror(errno));
        return -1;
    }

    /* accept connection */
    while(1)
    {    
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof client_addr;
        int client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addr_len);
        if(-1 == client_fd)
        {
            printf("accept connection::%s\n", strerror(errno));
            return -1;
        }

        int size = 1;
        char buf[BUFFER_SIZE];
        while(1)
        {
            size = read(client_fd, buf, sizeof buf);
            if(size == 0)
            {
                puts("Server:: Client disconnected");
                break;
            }
            buf[size] = '\0';
            printf("server receive::%s\n", buf);
        }

        close(client_fd);
    }    
    return EXIT_SUCCESS;
}
