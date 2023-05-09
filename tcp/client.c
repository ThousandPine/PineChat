#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>

#define BUFFER_SIZE 1024

void* recv_msg(void *arg_fd)
{
    int     fd = *(int *)arg_fd;
    int     size;
    char    buf[BUFFER_SIZE];

    while(1)
    {
        size = recv(fd, buf, sizeof buf, 0);
        buf[size] = '\0';
        printf("client receive::%s\n", buf);
    }
}

void* send_msg(void *arg_fd)
{
    int     fd = *(int *)arg_fd;
    char    buf[BUFFER_SIZE];

    while(1)
    {
        printf("input_msg::");
        scanf("%s", buf);
        send(fd, buf, strlen(buf), 0);        
    }
}

int main(int argc, char *argv[])
{
    if (3 != argc)
    {
        printf("Usage:%s hostname portnumber\n", argv[0]);
        return EXIT_FAILURE;
    }

    // put your code here

    /* create socket */
    int     client_fd = socket(AF_INET, SOCK_STREAM, 0);

    if (-1 == client_fd)
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

    /* connect to server */
    if(-1 == connect(client_fd, (struct sockaddr *)&server_addr, sizeof server_addr))
    {
        printf("create socket:: %s\n", strerror(errno));
        return -1;
    }

    /* create thread communication with server */
    int         ret;
    pthread_t   recv_thread;
    pthread_t   send_thread;
    
    ret = pthread_create(&recv_thread, NULL, recv_msg, (void *)&client_fd);
    if(0 != ret)
    {
        perror("==========");
        printf("create recv thread failed code %d\n", ret);
        return -1;
    }
    
    ret = pthread_create(&send_thread, NULL, send_msg, (void *)&client_fd);
    if(0 != ret)
    {
        printf("create send thread failed code %d\n", ret);
        return -1;
    }

    pthread_join(recv_thread, NULL);
    pthread_join(send_thread, NULL);

    return EXIT_SUCCESS;
}
