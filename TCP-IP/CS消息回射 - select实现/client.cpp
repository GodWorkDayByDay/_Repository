#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while (0)

ssize_t readn(int fd, void* buf, size_t count)
{
    size_t nleft = count; // 剩余要读取的字节数
    ssize_t nread; // 每次读取的字节数
    char* bufp = (char*)buf;
    while (nleft > 0)
    {
        if ((nread = read(fd, bufp, nleft)) < 0)
        {
            if(errno == EINTR)
                continue;

            return -1;
        }

        if(nread == 0) // 对等方关闭
            return count - nleft;

        nleft -= nread;
        bufp += nread;
    }

    return count;
}

ssize_t writen(int fd, void* buf, size_t count)
{
    size_t nleft = count; // 剩余要读取的字节数
    ssize_t nwritten; // 每次读取的字节数
    char* bufp = (char*)buf;
    while (nleft > 0)
    {
        if ((nwritten = write(fd, bufp, nleft)) < 0)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }

        if (nwritten == 0)
            continue;

        nleft -= nwritten;
        bufp += nwritten;
    }

    return count;
}

ssize_t recv_peek(int sockfd, void* buf, size_t len)
{
    while (1)
    {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if (ret == -1 && errno == EINTR)
            continue;
        // 偷窥到数据就直接返回
        return ret;
    }
}

ssize_t readline(int sockfd, void* buf, size_t maxline)
{
    char* bufp = (char*)buf;
    int nleft = maxline;
    int nread;
    int ret;
    while (1)
    {
        ret = recv_peek(sockfd, bufp, nleft);
        if (ret < 0)
            return ret;
        if (ret == 0)
            return ret;
        nread = ret;
        int i;
        for (i = 0; i < nread; ++i)
        {
            if (bufp[i] == '\n')
            {
                ret = readn(sockfd, bufp, i+1);
                if (ret != i+1)
                    exit(EXIT_FAILURE);
                return ret;
            }
        }
        // 没有遇到\n
        if (nread > nleft)
            exit(EXIT_FAILURE);
        nleft -= nread;
        ret = readn(sockfd, bufp, nread);
        if (ret != nread)
            exit(EXIT_FAILURE);
        //继续下一次偷窥
        bufp += nread;
    }

    return -1;
}

void echo_cli(int sock)
{
    fd_set rset;
    FD_ZERO(&rset);

    // 检测标准输入是否产生了可读事件
    int nready;
    int maxfd;
    int fd_stdin = fileno(stdin); // 标准输入
    char recvbuf[1024] = {0};
    char sendbuf[1024] = {0};

    // 有两个文件描述符，fd_stdin 和 sock
    if(fd_stdin > sock)
        maxfd = fd_stdin;
    else
        maxfd = sock;
    while (1)
    {
        FD_SET(fd_stdin, &rset);
        FD_SET(sock, &rset);
        // 这里只有读的集合
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if (nready == -1)
            ERR_EXIT("select error");
        if (nready == 0)
            continue;

        // 如果检测到了事件, 那么 rset 就会发生改变, 里面会包含哪些套接口发生了事件
        if (FD_ISSET(sock, &rset))
        {
            // 套接口产生了可读, 按行读取
            int ret = readline(sock, recvbuf, sizeof(recvbuf));
            if (ret == -1)
                ERR_EXIT("readline error");
            else if (ret == 0)
            {
                printf("server close\n");
                break;
            }

            // 显示出来
            fputs(recvbuf, stdout);
            memset(recvbuf, 0, sizeof(recvbuf));
        }
        if (FD_ISSET(fd_stdin, &rset))
        {
            // 标准输入产生事件,输入缓冲区有内容，用 fgets 去清空
            if(fgets(sendbuf, sizeof(sendbuf), stdin) == NULL)
                break;
            write(sock, sendbuf, strlen(sendbuf));
            memset(sendbuf, 0, sizeof(sendbuf));
        }
    }
    close(sock);
}

void handle_sigpipe(int sig)
{
    printf("recv a sig = %d\n", sig);
}

int main(void)
{
    signal(SIGPIPE, handle_sigpipe);
    int sock; //创建一个套接字
    if((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) // 用 AF_INET 和 PF_INET 都可以，前两个参数已经可确定是 TCP，所以第三个参数可以置 0
        ERR_EXIT("socket_failure");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);

    // 自己显式指定服务器端地址
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // 客户端不需要绑定（bind）, 也不需要监听（listen）, 直接连接过去就可以
    if (connect(sock, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("connect_failure");

    // 连接成功，查看本地的端口和地址
    struct sockaddr_in localaddr;
    socklen_t addrlen = sizeof(localaddr);
    if (getsockname(sock, (struct sockaddr*)&localaddr, &addrlen) < 0)
        ERR_EXIT("getsockname error");

    printf("IP = %s, port = %d\n", inet_ntoa(localaddr.sin_addr), ntohs(localaddr.sin_port));

    echo_cli(sock);

    return 0;
}
