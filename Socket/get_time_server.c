#include "unp.h"

int main(int argc, char* argv[])
{
    int listenfd, connfd;
    struct sockaddr_in server_addr;
    char buff[BUFFSIZE];
    time_t ticks;

    /* 创建监听套接字 */
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&server_addr, sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(13);
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    /* 命名套接字 */
    Bind(listenfd, (SA *)&server_addr, sizeof(server_addr));

    /* 监听套接字 */
    Listen(listenfd, LISTENQ);

    for( ; ; ) 
    {
        connfd = Accept(listenfd, (SA *)NULL, NULL);
        ticks = time(NULL); /* 获取时间 */
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));
        Close(connfd);
    }
    Close(listenfd);
    return 0;
}
