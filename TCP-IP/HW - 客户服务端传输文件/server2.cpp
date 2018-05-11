#include <stdio.h>
#include <algorithm>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <errno.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <signal.h>

using namespace std;

#define ERR_EXIT(m) \
    do \
    { \
        perror(m); \
        exit(EXIT_FAILURE); \
    }while (0)

struct Packet
{
    int len;
    char buffer[1024];
};

class Server
{
public:

    Server(sa_family_t sin_family, in_port_t sin_port, in_addr_t s_addr)
    {
        memset(&m_server_addr, 0, sizeof(m_server_addr));
        m_server_addr.sin_family      = sin_family;
        m_server_addr.sin_port        = htons(sin_port);
        m_server_addr.sin_addr.s_addr = htonl(s_addr);

        m_fd = -1;
       m_client_fd = -1;
    }

    /**
     * 从 fd 读取 count 个字节，保存到 buf 中，并返回已读取的字节数。
     * 循环进行读取，直到读取的字节数为 count；若对方关闭，则
     * 不再读取直接返回已读到的数据。
     */
    ssize_t read_n(int & fd, void* buf, size_t count)
    {
        size_t n_left = count; // 未读的字节数
        ssize_t n_read = 0; // 已读的字节数
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_read = read(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // 被信号中断
                    continue;

                ERR_EXIT("server read function failed! ");
                return -1;
            }
            else if (n_read == 0)
            {
                printf("client closed!\n");
                fd = -1;
                return count - n_left;
            }

            buffer += n_read;
            n_left -= n_read;
        }

        return count;
    }

    /**
     * 向 fd 写入 buffer 的前 count 个字节，并返回已写的字节数。
     */
    ssize_t write_n(int & fd, void* buf, size_t count)
    {
        size_t n_left = count; // 未写的字节数
        ssize_t n_written = 0;  // 已写的字节数
        char* buffer = (char*)buf;

        while (n_left > 0)
        {
            if ((n_written = write(fd, buffer, n_left)) < 0)
            {
                if (errno == EINTR) // 被信号中断
                    continue;

                ERR_EXIT("server write function failed! ");
                return -1;
            }
            else if (n_written == 0)
                continue;

            buffer += n_written;
            n_left -= n_written;
        }

        return count;
    }

    // 开启服务端
    void start()
    {
        // 避免僵尸进程
        signal(SIGCHLD, SIG_IGN);

        // 用 AF_INET 和 PF_INET 都可以，前两个参数已经可确定是 TCP，所以第三个参数可以置 0
        if ((m_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
            ERR_EXIT("server socket function failed! ");

        // 绑定之前开启地址重复利用
        int on = 1;
        if (setsockopt(m_fd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) < 0)
            ERR_EXIT("server setsockopt function failed! ");

        // 接下来进行绑定, 将该套接字与一个本地地址进行绑定, 需要将 IPv4 地址结构强制转换为通用地址结构
        if (bind(m_fd, (struct sockaddr*)&m_server_addr, sizeof(m_server_addr)) < 0)
            ERR_EXIT("server bind function failed! ");

        // 接下来是监听，将 socket 从 close 状态转为监听状态才能够接受连接
        if(listen(m_fd, SOMAXCONN) < 0)
            ERR_EXIT("server listen function failed! ");


        // 定义一个客户端地址
        struct sockaddr_in client_addr;
        socklen_t addr_len = sizeof(client_addr);

        pid_t pid;
        while (1)
        {
            m_client_fd = accept(m_fd, (sockaddr*)&client_addr, &addr_len);

            if (m_client_fd == -1)
                ERR_EXIT("server accept function failed! ");

            // 输出连接的客户端的信息
            printf("ip = %s, port = %d\n", inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            pid = fork();
            if (pid < 0)
                ERR_EXIT("server fork function failed\n ");

            // 子进程处理文件传输
            if (pid == 0)
            {
                Packet recv_packet;
                while (1)
                {
                    // 得到文件名
                    memset(&recv_packet, 0, sizeof(recv_packet));
                    int ret = read_n(m_client_fd, &recv_packet.len, sizeof(Packet::len));
                    if (ret == -1)
                        ERR_EXIT("server read_n function failed! ");
                    else if (ret < (int)sizeof(Packet::len))
                        return;
                    int n = ntohl(recv_packet.len);
                    ret = read_n(m_client_fd, recv_packet.buffer, n);
                    if (ret == -1)
                        ERR_EXIT("server read_n function failed! ");
                    else if (ret < n)
                        return;

                    // 在服务端打开或创建这个文件
                    if ((m_file = fopen(recv_packet.buffer, "a+")) == NULL)
                        ERR_EXIT("file open failed! ");

                    // 得到文件大小
                    memset(&recv_packet, 0, sizeof(recv_packet));
                    ret = read_n(m_client_fd, &recv_packet.len, sizeof(Packet::len));
                    if (ret == -1)
                        ERR_EXIT("server read_n function failed! ");
                    else if (ret < (int)sizeof(Packet::len))
                        return;
                    n = ntohl(recv_packet.len);
                    ret = read_n(m_client_fd, recv_packet.buffer, n);
                    if (ret == -1)
                        ERR_EXIT("server read_n function failed! ");
                    else if (ret < n)
                        return;
                    long int file_size = 0;
                    memcpy(&file_size, recv_packet.buffer, sizeof(long int));

                    printf("file size is %ld\n", file_size);

                    // 接收文件数据
                    while (file_size > 0)
                    {
                        memset(&recv_packet, 0, sizeof(recv_packet));

                        ret = read_n(m_client_fd, &recv_packet.len, sizeof(Packet::len));

                        if (ret == -1)
                            ERR_EXIT("server read_n function failed! ");
                        else if (ret < (int)sizeof(Packet::len))
                            return;

                        n = ntohl(recv_packet.len);
                        ret = read_n(m_client_fd, recv_packet.buffer, n);

                        file_size -= ret;

                        if (ret == -1)
                            ERR_EXIT("server read_n function failed! ");
                        else if (ret < n)
                            return;

                        ret = fwrite(recv_packet.buffer, sizeof(char), n, m_file);

                        if (ret < n)
                            ERR_EXIT("server file fwrite function failed! ");
                    }

                    printf("file saved success!\n");
                    fclose(m_file);
                }
            }
            else // 父进程继续在 accept 阻塞，等待新客户连接
            {
                close(m_client_fd);
            }
        }
    }

private:

    sockaddr_in m_server_addr;
    int         m_fd;
    int         m_client_fd;
    FILE*       m_file;
};

int main()
{

    Server server(AF_INET, 5188, INADDR_ANY);
    server.start();

    return 0;
}
