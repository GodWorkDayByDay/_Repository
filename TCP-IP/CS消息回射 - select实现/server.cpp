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
#include <sys/wait.h>

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while (0)

ssize_t readn(int fd, void* buf, size_t count)
{
    // 由于不能保证一次能够读取 count 个字节, 因此我们需要循环进行读取,
    // 直到读取的字节数为count
    size_t nleft = count;
    ssize_t nread;
    char* bufp = (char*)buf;
    while (nleft > 0)
    {
        if ((nread = read(fd, bufp, nleft)) < 0)
        {
            if(errno == EINTR) // 如果信号中断
                continue;

            return -1;
        }

        if (nread == 0) // 表示对等方关闭，这里直接返回
            return count - nleft;

        nleft -= nread; // 每次读取后剩余的字节数
        bufp += nread;
    }

    return count;
}

ssize_t writen(int fd, void* buf, size_t count)
{
    // 我们每次希望写入的字节数为 count
    size_t nleft = count;
    ssize_t nwritten;
    char* bufp = (char*)buf;
    while (nleft > 0)
    {
        if ((nwritten = write(fd, bufp, nleft)) < 0)
        {
            if(errno == EINTR)
                continue;
            return -1;
        }

        if (nwritten == 0)  // 什么都没发生
            continue;

        nleft -= nwritten; // 每次写后剩余要写的字节数
        bufp += nwritten;
    }

    return count;
}

ssize_t recv_peek(int sockfd, void* buf, size_t len)
{
    // 该函数可以从套接口接收数据, 但是并不将数据从缓冲区中移除
    while (1)
    {
        int ret = recv(sockfd, buf, len, MSG_PEEK);
        if(ret == -1 && errno == EINTR) // 读到数据就返回，否则就返回
            continue;

        return ret;
    }
}

ssize_t readline(int sockfd, void*buf, size_t maxline)
{
    // 读取过程不一定要读取 maxline 个字节, 只要遇到 \n 就可以返回
    int ret;
    int nread;
    char* bufp = (char*)buf;
    int nleft = maxline;
    while (1)
    {
        ret = recv_peek(sockfd, bufp, nleft);
        if(ret < 0)
            return ret;
        else if(ret == 0)
            return ret;

        nread = ret;
        int i;
        for (i = 0; i < nread; ++i)
        {
            if (bufp[i] == '\n')
            {
                //我们的 recv_peek 只是偷窥一下数据, 并没有移走数据,
                // 所以这里用 readn 从缓冲区中移除已偷窥的数据
                ret = readn(sockfd, bufp, i+1);
                if(ret != i+1)
                    exit(EXIT_FAILURE);
                return ret;
            }
        }


        if(nread > nleft) // 没有遇到 \n
            exit(EXIT_FAILURE);

        // 把读到的数据 nread 个字节从缓冲区中移走
        nleft -= nread;
        ret = readn(sockfd, bufp, nread);
        if(ret != nread)
            exit(EXIT_FAILURE);

        bufp += nread; // 继续下一次的偷窥, 需偏移
    }
    return -1;
}

void echo_srv(int conn)
{
    char recvbuf[1024];
    while (1)
    {
        memset(&recvbuf, 0, sizeof(recvbuf));
        int ret = readline(conn,  recvbuf, 1024);
        if (ret == -1)
            ERR_EXIT("read failure");

        if (ret == 0)
        {
            printf("client close\n");
            break;
        }
        fputs(recvbuf, stdout);
        writen(conn, recvbuf, strlen(recvbuf));
    }
}

void handle_sigchld(int sig)
{
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

int main(void)
{
    // 避免僵尸进程
    // signal(SIGCHLD, SIG_IGN);
    signal(SIGCHLD, handle_sigchld);

    int listenfd;
    if((listenfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) // 用 AF_INET 和 PF_INET 都可以，前两个参数已经可确定是 TCP，所以第三个参数可以置 0
        ERR_EXIT("socket_failure");

    struct sockaddr_in servaddr;
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(5188);

    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 表示本机的任意地址，推荐使用（转换成网络字节序）
    /*
    也可以自己显式指定
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
    或者
    inet_aton("127.0.0.1", &servaddr.sin_addr);
    */

    // 绑定之前开启地址重复利用
    int on = 1;
    if (setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
        ERR_EXIT("setsockopt_failure");

    //接下来进行绑定, 将该套接字与一个本地地址进行绑定, 需要将 IPv4 地址结构强制转换为通用地址结构
    if (bind(listenfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
        ERR_EXIT("bind_failure");

    // 接下来是监听，将 socket 从 close 状态转为监听状态才能够接受连接
    if(listen(listenfd, SOMAXCONN) < 0)
        ERR_EXIT("listen_failure");

    // 定义一个对方的地址
    struct sockaddr_in peeraddr;
    socklen_t peerlen;
    int conn; // 一个新的套接字，称为已连接套接字(主动套接字)

    int client[FD_SETSIZE]; // select 最多能处理的事件个数
    int i;
    for (i = 0; i < FD_SETSIZE; ++i)
        client[i] = -1; // 初始化，-1 表示空闲状态
    int maxi = 0; // 最大不空闲位置

    int nready;
    int maxfd = listenfd; // 3
    fd_set rset; // 定义一个读集合
    fd_set allset;
    FD_ZERO(&rset);
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset); // 先把监听套接口加进去
    while (1)
    {
        rset = allset;
        nready = select(maxfd+1, &rset, NULL, NULL, NULL);
        if (nready == -1)
        {
            if(errno == EINTR)
                continue;
            ERR_EXIT("select");
        }
        if (nready == 0)
            continue;
        if (FD_ISSET(listenfd, &rset))
        {
            peerlen = sizeof(peeraddr);
            // 监听套接口产生事件
            conn = accept(listenfd, (struct sockaddr*)&peeraddr, &peerlen);
            if (conn == -1)
                ERR_EXIT("accept error");
            for (i = 0; i < FD_SETSIZE; ++i)
            {
                if (client[i] < 0)
                {
                    // 找一个空闲位置把该套接口放进去
                    client[i] = conn;
                    if (maxi < i)
                        maxi = i;
                    break;
                }
            }
            if (i == FD_SETSIZE)
            {
                fprintf(stderr, "too many clients\n");
                exit(EXIT_FAILURE);
            }
            printf("ip = %s, port = %d\n", inet_ntoa(peeraddr.sin_addr), ntohs(peeraddr.sin_port));

            FD_SET(conn, &allset);
            if (conn > maxfd)
                maxfd = conn;

            if (--nready <= 0)
                continue;
        }

        // 已连接套接口也可能产生事件
        for (i = 0; i < FD_SETSIZE; ++i)
        {
            conn = client[i];
            if (conn == -1)
                continue;
            if (FD_ISSET(conn, &rset))
            {
                // 意味着产生了可读事件
                char recvbuf[1024] = {0};
                int ret = readline(conn, recvbuf, 1024);
                if (ret == -1)
                    ERR_EXIT("readline error");
                if (ret == 0)
                {
                    // 对等方关闭
                    printf("client close\n");
                    FD_CLR(conn, &allset); // 将该套接口清除
                    client[i] = -1;
                }
                fputs(recvbuf, stdout);
                writen(conn, recvbuf, strlen(recvbuf));

                if (--nready <= 0)
                    break;
            }
        }
    }

    return 0;
}
